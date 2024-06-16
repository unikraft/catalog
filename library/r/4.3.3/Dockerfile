FROM rocker/r-ver:4.3.3 as build

RUN mkdir /home/tmp

FROM scratch

ENV R_HOME=/usr/local/lib/R

# R specific files (libraries, excutable and config files)
COPY --from=build /usr/local/lib/R/lib/libR.so /lib/libR.so
COPY --from=build /usr/local/lib/R /usr/local/lib/R

# For R_TempDir
COPY --from=build /home/tmp /tmp

# Libraries
COPY --from=build /usr/lib/x86_64-linux-gnu/lapack/liblapack.so.3 /usr/lib/x86_64-linux-gnu/lapack/liblapack.so.3
COPY --from=build /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

COPY --from=build /usr/lib/x86_64-linux-gnu/libc.so.6 \
                  /usr/lib/x86_64-linux-gnu/liblapack.so.3 \
                  /usr/lib/x86_64-linux-gnu/libacl.so.1 \
                  /usr/lib/x86_64-linux-gnu/libicuuc.so.70 \
                  /usr/lib/x86_64-linux-gnu/libselinux.so.1 \
                  /usr/lib/x86_64-linux-gnu/libicui18n.so.70 \
                  /usr/lib/x86_64-linux-gnu/libicudata.so.70 \
                  /usr/lib/x86_64-linux-gnu/libblas.so.3 \
                  /usr/lib/x86_64-linux-gnu/libopenblas.so.0 \
                  /usr/lib/x86_64-linux-gnu/libm.so.6 \
                  /usr/lib/x86_64-linux-gnu/libreadline.so.8 \
                  /usr/lib/x86_64-linux-gnu/libpcre2-8.so.0 \
                  /usr/lib/x86_64-linux-gnu/liblzma.so.5 \
                  /usr/lib/x86_64-linux-gnu/libbz2.so.1.0 \
                  /usr/lib/x86_64-linux-gnu/libz.so.1 \
                  /usr/lib/x86_64-linux-gnu/libtirpc.so.3 \
                  /usr/lib/x86_64-linux-gnu/libgomp.so.1 \
                  /usr/lib/x86_64-linux-gnu/libtinfo.so.6 \
                  /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 \
                  /usr/lib/x86_64-linux-gnu/libstdc++.so.6 \
                  /usr/lib/x86_64-linux-gnu/libgcc_s.so.1 \
                  /usr/lib/x86_64-linux-gnu/libgfortran.so.5 \
                  /usr/lib/x86_64-linux-gnu/libkrb5.so.3 \
                  /usr/lib/x86_64-linux-gnu/libk5crypto.so.3 \
                  /usr/lib/x86_64-linux-gnu/libcom_err.so.2 \
                  /usr/lib/x86_64-linux-gnu/libkrb5support.so.0 \
                  /usr/lib/x86_64-linux-gnu/libkeyutils.so.1 \
                  /usr/lib/x86_64-linux-gnu/libresolv.so.2 \
                  /usr/lib/x86_64-linux-gnu/libquadmath.so.0 \
                  /usr/lib/x86_64-linux-gnu/

# Copy helloworld.R file
COPY ./helloworld.R /helloworld.R
