# Makefile
#
# Purpose: Run c test with Unity Unity.
# 
# Site: https://dirack.github.io
# 
# Programer: Rodolfo A C Neves (Dirack) 06/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Uncomment the line below to run on a CENTOS system. Or call make as 'make CENTOS=1'
#CENTOS=1 

DEP = ../vfsacrsnh_lib.c
UNITY = Unity/unity.c

all:	Test_vfsacrsnh_lib.x

%.x:	%.c
ifdef CENTOS
	gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf -lopenblas -g
	./$@
	rm $@
else
	gcc -I$$RSFSRC/include -L$$RSFSRC/lib $< $(DEP) $(UNITY) -o $@ -lm -lrsf 
	./$@
	rm $@
endif

time:	optimization_test/SConstruct
	cd optimization_test && scons --clean && scons dataCube.rsf && scons --debug=time