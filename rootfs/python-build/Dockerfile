# https://github.com/revsys/optimized-python-docker/blob/master/Dockerfile
# https://github.com/docker-library/python/blob/master/3.12/slim-bullseye/Dockerfile

FROM ubuntu:22.04 as base

ENV PATH /usr/local/bin:$PATH

RUN set -xe ; \
	apt update ; \
	apt install -yqq build-essential ; \
	apt install -yqq make ; \
	apt install -yqq curl ; \
	apt install -yqq tar ; \
	apt install -yqq libexpat-dev ; \
	apt install -yqq zlib1g-dev ; \
	apt install -yqq zlib1g-dev

ARG PYTHON_VERSION=3.12.0
ENV PYTHON_VERSION ${PYTHON_VERSION}

ENV SRCDIR /python
RUN set -xe ; \
	mkdir -p ${SRCDIR}/build ; \
	curl -sL "https://www.python.org/ftp/python/${PYTHON_VERSION}/Python-${PYTHON_VERSION}.tar.xz" | \
	tar -xJC ${SRCDIR} --strip-components=1 -f -

WORKDIR ${SRCDIR}/build

RUN set -xe ; \
	gnuArch="$(dpkg-architecture --query DEB_BUILD_GNU_TYPE)" ;  \
	../configure \
	--build="$gnuArch" \
	--enable-shared

RUN set -xe ; \
	make -j $(( 1 * $( egrep '^processor[[:space:]]+:' /proc/cpuinfo | wc -l ) )) ; \
	make install

RUN set -xe ; \
	find /usr/local -type f -name "*.so" -exec strip --strip-unneeded {} + ; \
	find /usr/local -type f -name "*.so" | ldconfig ; \
	find /usr/local -depth \
	\( \
		\( -type d -a \( -name test -o -name tests -o -name __pycache__ \) \) \
			-o \
		\( -type f -a \( -name '*.pyc' -o -name '*.pyo' -o -name '*.exe' \) \) \
	\) -exec rm -rf '{}' +;

RUN set -xe ; \
	rm -fr /usr/local/lib/python*/config-*

FROM scratch

COPY --from=base /usr/local/bin/ /usr/local/bin/
COPY --from=base /usr/local/lib/ /usr/local/lib/
COPY --from=base /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=base /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=base /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2
COPY --from=base /etc/ld.so.cache /etc/ld.so.cache
