This is POC for running the package test with preloaded module\

```/src``` contains all the scripts that will be built into  the shared object.\
```build.sh``` converts the scripts in /src so into a /build directory that is created run-time.\
```test/preload/test.c``` sample script- will be replaced by actual tests.\
```test/preload/run_tests.sh``` run the test scripts.

