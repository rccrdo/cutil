LIB_HEADERS_INSTALL_DIR = /usr/local/include/cu


# ************           install          **************
.PHONY: install
 install:
	# copy headers
	mkdir -p $(LIB_HEADERS_INSTALL_DIR)
	cp -a *.h $(LIB_HEADERS_INSTALL_DIR)


# ************       clean and purge      **************
.PHONY: clean
clean: 
	-rm -f *~
	-rm -f *#

