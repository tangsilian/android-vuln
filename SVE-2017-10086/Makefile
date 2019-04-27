#!/usr/bin/make
#
#     mtpwn - PoC exploit for a vulnerability of Samsung's Android
#             phones that allows an attacker to access phone storages
#             via USB, bypassing lock screen and/or "Charge only" mode.
#             It requires libmtp.
#
#     Copyright (C) 2017  Salvatore Mesoraca <s.mesoraca16@gmail.com>
#
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC=gcc
CFLAGS=-Wall -pedantic -std=gnu90 -O2 \
       -fstack-protector --param=ssp-buffer-size=4 \
       -Wformat -Werror=format-security -fPIE
LDFLAGS=-lmtp -pie -s

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

mtpwn: mtpwn.o
	gcc -o $@ $< $(LDFLAGS)

mtpwn.pdf: README.rst
	rst2pdf $< -o $@

mtpwn.tgz:
	git archive --format=tar.gz --prefix=mtpwn/ master -o $@

clean:
	-rm -f *~ *.o 2>/dev/null

distclean: clean
	-rm -f mtpwn.pdf mtpwn.tgz mtpwn

.PHONY: clean distclean
