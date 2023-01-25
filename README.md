# File-System Benchmarks
This is a set of custom benchmarks to measure the speed of common file-system operations: sequential/random **read** and **write**; file **creation**, **deletion** and directory **listing**.

We have used these benchmarks to measure the speed of the Unikraft 9pfs implementation and compare it against the Unikraft virtiofs [implementation](https://github.com/astrynzha/virtiofs_unikraft/tree/master).

The benchmarks can be run on standard Linux as well as on Unikraft. We have used C macros to guard the appropriate code parts for each platform.
