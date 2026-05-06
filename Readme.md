# MO0VEY Graphics Repository

This repository should stay focused on the semester project only.

## Strict repository rule
Only files should be committed that are one of the following:
- required to build or run the semester project,
- part of the submitted documentation,
- not generated automatically during build or local setup.

Everything else should stay local.

## What belongs in the repository
- `Beadando/`: source code, Makefile, runtime assets, project documentation
- `.gitignore`: local filtering rules for SDKs, build output, and unrelated coursework
- `Readme.md`: repository-level notes

## What must stay local only
- `c_sdk_220203/`: the course SDK is a local dependency and must not be pushed
- `Gyakorlatok/`: practice material is unrelated to the semester project
- downloaded runtime DLLs in the repository root
- generated binaries and object files in `Beadando/build/`
- development helpers and unused asset variants

## Why the SDK is not part of Git
The `c_sdk_220203/` folder was provided for the course, but it is still an external toolchain and example pack, not part of the semester-project source. It contains:
- compiler and runtime binaries,
- example programs,
- third-party DLLs,
- files that are not authored as part of this specific project.

That makes it an environment prerequisite, not submission content. The project may depend on that SDK locally, but the repository should only contain the project itself and clear build instructions for using the SDK.

## Local setup on Windows
1. Download or extract the course SDK next to the repository as `c_sdk_220203/`.
2. If texture loading fails with a missing `libpng16-16.dll`, copy that DLL into `c_sdk_220203/MinGW/bin/`.
3. Build from `Beadando/` with either `..\c_sdk_220203\shell.bat` then `make`, or directly with `..\c_sdk_220203\MinGW\bin\mingw32-make.exe`.

## Submission notes
- Only runtime assets should remain in `Beadando/assets/`.
- Large asset packs should be uploaded separately and linked from `Beadando/README.md`.
- The unpacked project should stay comfortably below the 200 MB target.

The detailed semester-project concept and architecture plan are in `Beadando/README.md`.# MO0VEY Graphics Repository

This repository should stay focused on the semester project only.

## Strict repository rule
Only files should be committed that are one of the following:
- required to build or run the semester project,
- part of the submitted documentation,
- not generated automatically during build or local setup.

Everything else should stay local.

## What belongs in the repository
- `Beadando/`: source code, Makefile, runtime assets, project documentation
- `.gitignore`: local filtering rules for SDKs, build output, and unrelated coursework
- `Readme.md`: repository-level notes

## What must stay local only
- `c_sdk_220203/`: the course SDK is a local dependency and must not be pushed
- `Gyakorlatok/`: practice material is unrelated to the semester project
- downloaded runtime DLLs in the repository root
- generated binaries and object files in `Beadando/build/`
- development helpers and unused asset variants

## Why the SDK is not part of Git
The `c_sdk_220203/` folder was provided for the course, but it is still an external toolchain and example pack, not part of the semester-project source. It contains:
- compiler and runtime binaries,
- example programs,
- third-party DLLs,
- files that are not authored as part of this specific project.

That makes it an environment prerequisite, not submission content. The project may depend on that SDK locally, but the repository should only contain the project itself and clear build instructions for using the SDK.

## Local setup on Windows
1. Download or extract the course SDK next to the repository as `c_sdk_220203/`.
2. If texture loading fails with a missing `libpng16-16.dll`, copy that DLL into `c_sdk_220203/MinGW/bin/`.
3. Build from `Beadando/` with either `..\c_sdk_220203\shell.bat` then `make`, or directly with `..\c_sdk_220203\MinGW\bin\mingw32-make.exe`.

## Submission notes
- Only runtime assets should remain in `Beadando/assets/`.
- Large asset packs should be uploaded separately and linked from `Beadando/README.md`.
- The unpacked project should stay comfortably below the 200 MB target.

The detailed semester-project concept and architecture plan are in `Beadando/README.md`.