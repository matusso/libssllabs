# libssllabs
[![CI](https://github.com/matusso/libssllabs/actions/workflows/ci.yml/badge.svg)](https://github.com/matusso/libssllabs/actions/workflows/ci.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=matusso_libssllabs&metric=alert_status)](https://sonarcloud.io/dashboard?id=matusso_libssllabs)
<a href="https://scan.coverity.com/projects/matusso-libssllabs">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/8326/badge.svg"/>
</a>

<br><br>

C++ library (windows/linux/osx) to work with SSL<br>
Qualys SSL Labs: https://www.ssllabs.com/

libssllabs communicates with SSLLabs via API <br>
official documentation: https://github.com/ssllabs/ssllabs-scan/blob/stable/ssllabs-api-docs.md

###### Requirements

Need CMake 3.21+ and libcurl development headers:

```bash
apt-get install cmake libcurl4-openssl-dev
```

Initialize the RapidJSON submodule before configuring:

```bash
git submodule update --init --recursive
```

###### Build And Test

```bash
cmake -S . -B build -DSSLLABS_BUILD_TESTS=ON -DSSLLABS_BUILD_TOOLS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Pull requests now run the same `ctest` suite in GitHub Actions.
