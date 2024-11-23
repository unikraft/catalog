# stat

This is a simple introspection of the `stat` structure.
It prints, for all fields of the `stat` structure: the value, the size, the offset within the structure.

Built the program as a PIE executable by using:

```Bash
$ make
```

In order to run it, go first to the `rootfs/` folder:

```Bash
$ cd rootfs/

$ ../stat
 * st_dev:      value:      66309, size:  8, offset:  0
 * st_ino:      value:     935356, size:  8, offset:  8
 * st_mode:     value:      33204, size:  4, offset: 24
 * st_nlink:    value:          1, size:  8, offset: 16
 * st_uid:      value:       1000, size:  4, offset: 28
 * st_gid:      value:       1000, size:  4, offset: 32
 * st_rdev:     value:          0, size:  8, offset: 40
 * st_size:     value:          0, size:  8, offset: 48
 * st_blksize:  value:       4096, size:  8, offset: 56
 * st_blocks:   value:          0, size:  8, offset: 64
 * st_atim:     value:          0, size: 16, offset: 72
 * st_mtim:     value:          0, size: 16, offset: 88
 * st_ctim:     value:          0, size: 16, offset: 104

total size: 144
```
