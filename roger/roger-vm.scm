(use-modules (gnu)
             (gnu services configuration)
             (gnu services mail)
             (gnu services mcron)
             (gnu services shepherd)
             (gnu services web)
             (guix build-system gnu)
             (guix download)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (guix records)
             (srfi srfi-1))

(use-service-modules base networking ssh)
(use-package-modules admin bash certs curl linux lsof tls tmux)

;; Random notes. Don't read.
;; (service-extension shepherd-root-service-type FUNC)
;; FUNC needs to return a list of (shepherd-service)
;; shepherd-root-service-type will "consume" this list and make a shepherd
;; service for each of them
;;
;; (extend) used to extend only one thing, eg. list of rules, not eg. list for
;; rules AND package ???
;; if two instances (processes) of service needed -> two services with two
;; different configs, for example:
;; (service nginx-service-type config1)
;; (service nginx-service-type config2)
;; ???
;;
;; /!\
;; (service nginx-service-type CONFIG) !=
;; (define my-service ... (service-extension nginx-service-type FUNC))) ???
;;
;; Seems like calling one (service-extension SERVICE) does automatically
;; instatiate one SERVICE of this type with its default config. If no default
;; config is set, this fails.
;; Is shepherd-root-service-type instatiated like that? With a default
;; configuration? Or is it installed with a (service shepherd-root-service-type)
;; somewhere?

;; Modifying an nginx-service-type's shepherd-service so that it requires
;; another service (eg. generate-certs), needs to be done by inherint the
;; service type data type, because a (service-extension) wouldn't be enough.

;; Extensible service:
;; (compose) takes care of the list of extensions, eg:
;; (service-extension shepherd-root-service-type (lambda (x) (list....)))
;; (service-extension shepherd-root-service-type (lambda (x) (list....)))
;; (compose concatenate) would concatenate all the lists, and the result would
;; look like: (list (shepherd-service ...) (shepherd-service ...))
;; (extend) takes care of "injecting" the composed value into the service's
;; value (configuration)

;; activation-service-type can be used to create directories that are required
;; by the service before it is started. But is it really started before?

;; If a service-type ORIGINAL doesn't have a default-value and another
;; service-type EXTENDED uses this service type as an extension, you will get
;; the following possible errors:
;; - If no instance of ORIGINAL is declared in operating-sysem.services
;; `guix system: error: no target of type 'ORIGINAL' for service 'EXTENDED'`
;; - If there is an instance of ORIGINAL in operating-sysem.services with
;; ORIGINAL-CONFIGURATION
;; `guix system: error: ORIGINAL-configuration: source expression failed to match any pattern`

;; Looks like define-configuration is meant to be used when the whole config
;; file can be serialized from the said config
;; gnu/services/configuration.scm
;; (define-configuration NAME
;;  (ELEMENT (TYPE DEFAULT_VALUE) DOC)...)

;; From guix/records.scm:
;; (define-syntax define-record-type*
;; [...]
;; It is possible to copy an object 'x' created with 'thing' like this:
;;   (thing (inherit x) (name \"bar\"))

;; The 'source expression failed to match any pattern' error seems to occur
;; when we set a record field that doesn't exist

(define-record-type* <auditd-configuration> auditd-configuration
  make-auditd-configuration
  auditd-configuration?
  (package     auditd-configuration-package
               (default audit))
  (audit-rules auditd-configuration-audit-rules
               (default '())))

(define (auditd-shepherd-service config)
  (let* ((auditd-package (auditd-configuration-package config)))
    (list (shepherd-service
           (documentation "Auditd allows you to audit file system accesses.")
           (provision '(auditd))
           (start #~(make-forkexec-constructor
                     (list (string-append #$auditd-package "/sbin/auditd") "-l")
                     #:pid-file "/var/run/auditd.pid"))
           (stop #~(make-kill-destructor))))))

(define (auditd-etc-service config)
  (let* ((audit-rules (auditd-configuration-audit-rules config)))
    (list
     `("audit/audit.rules"
       ,(plain-file
         "audit.rules"
         (fold (lambda (rule rules)
                 (string-append rules rule "\n"))
               "" audit-rules)))
     ;; FIXME Should use auditd-configuration
     `("audit/auditd.conf" ,(local-file "vm-files/auditd.conf")))))

(define (auditd-activation-service config)
  #~(begin
      (use-modules (guix build utils))
      ;; FIXME Should use auditd-configuration
      (mkdir-p "/var/log/audit")
      (system* "/run/current-system/profile/sbin/auditctl" "-R" "/etc/audit/audit.rules")))

(define auditd-service-type
  (service-type
   (name 'auditd)
   (description "Allows auditing file system accesses.")
   (extensions
    (list
     (service-extension shepherd-root-service-type auditd-shepherd-service)
     (service-extension etc-service-type auditd-etc-service)
     (service-extension activation-service-type auditd-activation-service)
     (service-extension profile-service-type
                        (compose list auditd-configuration-package))))
   (compose concatenate)
   (extend (lambda (config rules)
             (auditd-configuration
              (inherit config)
              (audit-rules (append (auditd-configuration-audit-rules config)
                                   rules)))))
   (default-value (auditd-configuration))))

(define monitor-crontab-service-type
  (service-type
   (name 'monitor-crontab)
   (description "Monitor /etc/crontab")
   (extensions
    (list
     (service-extension
      auditd-service-type
      (lambda _
        '("# Delete all the previous rules"
          "-D"
          "# Watch /etc/crontab for writes and attributes changes"
          "-w /etc/crontab -p wa -k monitor-crontab"
          "# Lockdown the rules (reboot required)"
          "-e 2")))
     (service-extension
      mcron-service-type
      (lambda _
        (list #~(job "0 0 * * *"
                     "(/bin/sh /root/scripts/monitor-crontab.sh 2>&1) >> /var/log/monitor_crontab.log"))))
     (service-extension
      special-files-service-type
      (lambda _
        `(("/root/scripts/monitor-crontab.sh" ,(local-file "vm-files/monitor-crontab.sh")))))))
   (default-value `())))

(define my-nginx-service-configuration
  (nginx-configuration
   (server-blocks
    (list
     (nginx-server-configuration
      (listen '("80"))
      (server-name '("default"))
      (raw-content '("return 301 https://$host$request_uri;")))
     (nginx-server-configuration
      (listen '("443 ssl"))
      (ssl-certificate "/etc/nginx/ssl/roger-skyline.sh.crt")
      (ssl-certificate-key "/etc/nginx/ssl/roger-skyline.sh.key")
      (server-name '("roger-skyline.sh"))
      (root "/srv/http/roger-skyline.sh/current"))))))

(define my-nginx-service-type
  (service-type
   (inherit nginx-service-type)
   (extensions
    (append
     (list (service-extension
            special-files-service-type
            (lambda _
              `(("/root/scripts/generate-certificate.sh"
                 ,(local-file "vm-files/generate-certificate.sh"))))))
     (map (lambda (se)
            (let ((se-target (service-extension-target se))
                  (se-compute (service-extension-compute se)))
              (cond ((eq? se-target activation-service-type)
                     (service-extension
                      activation-service-type
                      (lambda config
                        #~(begin
                            (system* "/run/current-system/profile/bin/sh" "/root/scripts/generate-certificate.sh")
                            #$(apply se-compute config)))))
                    (else se))))
          (service-type-extensions nginx-service-type))))))

(define my-opensmtpd-service-type
  (service-type
   (inherit opensmtpd-service-type)
   (extensions
    (map (lambda (se)
           (let ((se-target (service-extension-target se))
                 (se-compute (service-extension-compute se)))
             (cond ((eq? se-target activation-service-type)
                    (service-extension
                     activation-service-type
                     (lambda config
                     #~(begin
                         (use-modules (guix build utils))
                         (mkdir-p "/var/spool/mail")
                         #$(apply se-compute config)))))
                   (else se))))
         (service-type-extensions opensmtpd-service-type)))))


(define update-packages-service-type
  (let ((update-packages-command "/bin/sh /root/scripts/update-packages.sh"))
    (service-type
     (name 'update-packages-service-type)
     (description "Update the packages.")
     (extensions
      (list
       (service-extension
        mcron-service-type
        (lambda _
          ;; TODO Test
          (list #~(job "0 4 * * *" #$update-packages-command))))
       ;; /!\ The shepherd socket won't be available until the update is
       ;; finished
       (service-extension
        shepherd-root-service-type
        (lambda _
          (list
           (shepherd-service
            (documentation "Update the packages.")
            (requirement '(guix-daemon))
            (provision '(update-packages))
            (start #~(lambda _
                       ;; TODO Check when failing
                       (zero? (system #$update-packages-command))))
            (one-shot? #t)))))
       (service-extension
        special-files-service-type
        (lambda _
          `(("/root/scripts/update-packages.sh" ,(local-file "vm-files/update-packages.sh")))))))
     (default-value '()))))

(define firewall-service-type
  (service-type
   (name 'firewall-service-type)
   (description "Activate the firewall")
   (extensions
    (list
     (service-extension
      shepherd-root-service-type
      (lambda _
        (list
         (shepherd-service
          (documentation "Install the firewall")
          (requirement '(guix-daemon))
          (provision '(firewall))
          (start #~(lambda _
                     ;; TODO Check when failing
                     (zero? (system "(/run/current-system/profile/sbin/ip link set dev ens3 xdp obj /root/firewall.o 2>&1 && /run/current-system/profile/sbin/ip link set dev ens4 xdp obj /root/firewall.o 2>&1) > /var/log/firewall.log 2>&1"))))
          (one-shot? #t)))))
     (service-extension
      special-files-service-type
      (lambda _
        `(("/root/firewall.o" ,(local-file "vm-files/firewall.o")))))))
   (default-value '())))

;; TODO Modify original package?
;; Modify the iproute to pull libelf so that we can load ebpf programs with it
(use-package-modules bison dbm elf flex pkg-config)
(define-public my-iproute
  (package
    (name "my-iproute2")
    (version "5.5.0")
    (source (origin
              (method url-fetch)
              (uri (string-append
                    "mirror://kernel.org/linux/utils/net/iproute2/iproute2-"
                    version ".tar.xz"))
              (sha256
               (base32
                "0ywg70f98wgfai35jl47xzpjp45a6n7crja4vc8ql85cbi1l7ids"))))
    (build-system gnu-build-system)
    (arguments
     `( ;; There is a test suite, but it wants network namespaces and sudo.
       #:tests? #f
       #:make-flags (let ((out (assoc-ref %outputs "out")))
                      (list "DESTDIR="
                            (string-append "BASH_COMPDIR=" out
                                           "/etc/bash_completion.d")
                            (string-append "LIBDIR=" out "/lib")
                            (string-append "HDRDIR=" out "/include")
                            (string-append "SBINDIR=" out "/sbin")
                            (string-append "CONFDIR=" out "/etc")
                            (string-append "DOCDIR=" out "/share/doc/"
                                           ,name "-" ,version)
                            (string-append "MANDIR=" out "/share/man")))
       #:phases (modify-phases %standard-phases
                  (add-before 'install 'pre-install
                    (lambda _
                      ;; Don't attempt to create /var/lib/arpd.
                      (substitute* "Makefile"
                        (("^.*ARPDDIR.*$") ""))
                      #t)))))
    (inputs
     `(("db4" ,bdb)
       ("iptables" ,iptables)
       ("libmnl" ,libmnl)))
    (native-inputs
     `(("bison" ,bison)
       ("flex" ,flex)
       ("libelf" ,libelf)
       ("pkg-config" ,pkg-config)))
    ;; For tests.
    ;; ("libmnl" ,libmnl)
    ;; ("util-linux" ,util-linux)
    (home-page
     "https://wiki.linuxfoundation.org/networking/iproute2")
    (synopsis
     "Utilities for controlling TCP/IP networking and traffic in Linux")
    (description
     "Iproute2 is a collection of utilities for controlling TCP/IP networking
and traffic with the Linux kernel.  The most important of these are
@command{ip}, which configures IPv4 and IPv6, and @command{tc} for traffic
control.

Most network configuration manuals still refer to ifconfig and route as the
primary network configuration tools, but ifconfig is known to behave
inadequately in modern network environments, and both should be deprecated.")
    (license license:gpl2+)))

(operating-system
  (host-name "roger")
  (timezone "Europe/Paris")
  (locale "en_US.utf8")

  ;; Boot in "legacy" BIOS mode, assuming /dev/sdX is the
  ;; target hard disk, and "my-root" is the label of the target
  ;; root file system.
  (bootloader (bootloader-configuration
               (bootloader grub-bootloader)
               (terminal-outputs '(console))
               ;; TODO Add a menu-entry with (linux-arguments '("console=ttyS0"))
               (target "/dev/sdX")))
  (file-systems (cons (file-system
                        (device (file-system-label "my-root"))
                        (mount-point "/")
                        (type "ext4"))
                      %base-file-systems))

  ;; This is where user accounts are specified.  The "root"
  ;; account is implicit, and is initially created with the
  ;; empty password.
  (users (cons (user-account
                (name "user")
                (group "users")
                (password "$6$3irvmKQ65RKtni6J$MaagXd2HFvAYmHDNDw8.upMVtngfWZjHGXuxeYQtBJScQCCWgo8d18MJlKy6Xy2HO5Tud0nSBhjSvqEYwBKC4.")

                ;; Adding the account to the "wheel" group
                ;; makes it a sudoer.
                (supplementary-groups '("wheel")))
               %base-user-accounts))

  ;; Globally-installed packages.
  (packages (append (list curl lsof nss-certs openssl tmux my-iproute) %base-packages))

  (services (append (list
                     (static-networking-service "ens3" "172.16.0.2"
                                                #:netmask "255.255.255.252"
                                                #:gateway "172.16.0.1"
                                                #:name-servers '("1.1.1.1" "1.0.0.1"))
                     (static-networking-service "ens4" "10.0.0.1"
                                                #:netmask "255.255.255.252")
                     (service firewall-service-type)
                     ;; TODO Extract in var ?
                     (service openssh-service-type
                              (openssh-configuration
                               (permit-root-login #f)
                               (allow-empty-passwords? #f)
                               (challenge-response-authentication? #f)
                               (password-authentication? #f)
                               (public-key-authentication? #t)
                               (authorized-keys
                                `(("user" ,(local-file "vm-files/user.pub"))))
                               (port-number 9595)))
                     (service update-packages-service-type)
                     ;; monitor-crontab-service-type requires a working smtp
                     ;; daemon
                     (service my-opensmtpd-service-type
                              (opensmtpd-configuration
                               (config-file %default-opensmtpd-config-file)))
                     (service monitor-crontab-service-type)
                     (service my-nginx-service-type my-nginx-service-configuration))
                    %base-services)))
