(use-modules (gnu))

(use-service-modules base networking ssh)
(use-package-modules admin certs curl networking tls)

(operating-system
  (host-name "test")
  (timezone "Europe/Paris")
  (locale "en_US.utf8")

  ;; Boot in "legacy" BIOS mode, assuming /dev/sdX is the
  ;; target hard disk, and "my-root" is the label of the target
  ;; root file system.
  (bootloader (bootloader-configuration
               (bootloader grub-bootloader)
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
  (packages (append (list curl ethtool nss-certs openssl nmap tcpdump) %base-packages))

  (services (append (list
                     (static-networking-service "eth1" "172.16.0.3"
                                                #:netmask "255.255.255.0"
                                                #:gateway "172.16.0.1"
                                                #:name-servers '("1.1.1.1" "1.0.0.1"))
                     (static-networking-service "eth2" "10.0.0.2"
                                                #:netmask "255.255.255.252")
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
                               (port-number 9595))))
                    %base-services)))
