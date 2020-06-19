# Roger

Subject: [roger-skyline-1.5.en.pdf](roger-skyline-1.5.en.pdf)

Technologies used:
- [**Guix**](https://guix.gnu.org/)
- [**eBPF**](https://docs.cilium.io/en/latest/bpf/) and
  [**XDP**](https://en.wikipedia.org/wiki/Express_Data_Path)
- Linux veth, bridge and network namespace

Guix revision used:
```
guix pull -l
Generation 27   Apr 18 2020 10:55:18    (current)
  guix aa78c59
    repository URL: https://git.savannah.gnu.org/git/guix.git
    branch: master
    commit: aa78c596c9eaae946f779d8fa3c4125d08187648
```

TODO Pin guix/libbpf version

## Dependencies

- Clang
- Guix
- libguestfs

## Architecture

TODO Diagram

## Usage

Start the roger and test vm:

```sh
./start.sh
```

Run the tests:

```sh
./test.sh
```

## The Good

- There is some automated tests

## The Bad

- The network interfaces use `e1000` instead of `virtio-pci-net`
- The update locking mechanism could be improved
- The updates that are done at boot are backgrounded instead of being run in
  parallel in order not to lock the boot process

## The Ugly

- The partition is resized with libguestfs instead of directly being formatted
  at the proper size by guix
