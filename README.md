# Autarco Solar Data Fetcher and Display

## Dependencies

The system must have `libcurl` available.

Build requires `stdlib.h`, `stdio.h`, `string.h` and `time.h`.

## Building

As this is programme is expected to run on an embedded device or single board computer, compiling for size is generally recommended.

```bash
gcc -Os -s -I./include  main.c ./src/autarco.c -o autarco.exe
```

## Configuration

A TOML file is required for configuring the data fetcher, with the following as an example:

```TOML
[autarco]
site_id = "m00000000"
uname = "foo@bar.com"
pwd = "pwd"
outdir = "/some/path"
```

## Running

On Windows:

```powershell
.\autarco.exe /path/to/conf.toml
```