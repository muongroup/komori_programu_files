# -*- mode: makefile -*-
#***********************************************************************
# Makefile for PHITS by K.F, last revised 2016/03/10
#***********************************************************************

### Machine Dependent variables, please set your environment 
ENVFLAGS = LinIfort
# Linux Intel Fortran:                                     LinIfort
# Linux PGI Fortran:                                       LinPGIfort
# Linux gfortran:                                          LinGfort
# Windows gfortran (4.71 or later):                        WinGfort
# Windows Cygwin gfortran (4.7 or later):                  WinCygGfort
# Mac Intel fortran:                                       MacIfort
# Mac PGI fortran:                                         MacPGIfort
# Mac gfortran (4.71 or later):                            MacGfort
# SGI ICE X (JAEA supercomputer since Nov. 2015):          SGIICEX
# FX1 (you have to use "gmake" instead of "make"):         FX1
### If you succeeded in compiling PHITS in new environment, 
### please send your makefile to phits-office@jaea.go.jp

### If you want to use MPI, delete # in the next line
 USEMPI = true
### If you want to use OpenMP, delete # in the next line.
# USEOMP = true

### If you set USEOMP = true, 
### You have to set an environmental variable OMP_NUM_THREADS before executing PHITS.
### If you do not know the appropriate value of OMP_NUM_THREADS for your machine,
### please ask your machine administrator, or turn off USEOMP.

DEBUG ?= false

### If you want to make dependence (make.depend), you have to type
### make depend DEVEL=1

##### target name
ifeq ($(ENVFLAGS),)
 $(error Error! ENVFLAGS is not defined)
else
 TARGET   = /home/komori/phits300_muon
 ifeq ($(USEOMP),true)
  # check whether gfortran is used
  ifeq ($(findstring Gfort,$(ENVFLAGS)),Gfort)
   # if so, check the version and exit if it's newer than 4.8.x
   #   (taken from http://stackoverflow.com/questions/5188267/checking-the-gcc-version-in-a-makefile)
   GFVER_GTE49 := $(shell echo `gfortran -dumpversion | cut -f1-2 -d.` \>= 4.9 | sed -e 's/\./*100+/g' | bc )
   ifeq ($(GFVER_GTE49),1)
    $(error Can NOT compile a program w/ OpenMP enabled using gfortran 4.9 or newer)
   endif
  endif
  TARGET := $(TARGET)_OMP
 endif
 ifeq ($(USEMPI),true)
  # $(warning You may need to set the fortran compiler that is invoked from your mpifort command)
  TARGET := $(TARGET)_MPI
 endif
 ifeq ($(DEBUG),true)
  TARGET := $(TARGET)_DBG
 endif
endif

ifeq ($(ENVFLAGS),WinGfort)
 RM = del
else
 RM = rm
endif


### SRCS8
ifeq ($(USEMPI),true)
 SRCS8 = mpi-lin.f unix90.f
else
 SRCS8 = mpi-non.f unix90.f
endif

### Linux Intel Fortran
ifeq ($(ENVFLAGS),LinIfort)
 IntelFortran = true
 SRCS8  += mdp-uni90.f
 ifeq ($(DEBUG),true)
  FFLAGS = -O0 -fpconstant -g -traceback -fpe0 -fp-stack-check
 else
  FFLAGS = -O3 -fpconstant
 endif
 ifeq ($(USEOMP),true) 
  FFLAGS += -openmp  ### if -openmp does not work, try -qopenmp
 endif
 ifeq ($(USEMPI),true)
  FC = mpif90
###  LDLIBS = -lmpi ### -lmpi sometimes -lmpich, or not necessary
 else
  FC = ifort
 endif
endif

### Linux PGI Fortran
ifeq ($(ENVFLAGS),LinPGIfort)
 FC = pgfortran
 SRCS8  += mdp-uni90.f
 ifeq ($(DEBUG),true)
  FFLAGS = -O0 -g
 else
  FFLAGS = -O2 -Mipa=fast
 endif
 ifeq ($(USEOMP),true) 
  FFLAGS += -mp
 endif
 ifeq ($(USEMPI),true)
  FC = mpif90
  # FFLAGS += -Mmpi=mpich # for compiling w/ pgfortran
 endif
endif

### Linux, gfortran (Can NOT compile w/ OpenMP using gfortran v4.9.x and newer!!)
ifeq ($(ENVFLAGS),LinGfort)
 OtherGfortran = true
 FC        = gfortran
 SRCS8    += mdp-uni90.f
 FFLAGS    = -O1 -fdefault-double-8 -fdefault-real-8 -fdollar-ok
 ifeq ($(USEOMP),true)
  FFLAGS  += -fopenmp
 endif
 ifeq ($(USEMPI),true)
  FC       = mpifort
  LDLIBS   = -lmpi_usempi -lmpi_mpifh -lmpi
 endif
endif

### SGI ICE X (JAEA supercomputer since Nov. 2015)
ifeq ($(ENVFLAGS),SGIICEX)
 IntelFortran = true
 SRCS8  += mdp-uni90.f
 ifeq ($(DEBUG),true)
  FFLAGS = -O0 -fpconstant -g -traceback -fpe0 -fp-stack-check
 else
  FFLAGS = -O3 -fpconstant
 endif
 ifeq ($(USEOMP),true) 
  FFLAGS += -qopenmp
 endif
 ifeq ($(USEMPI),true)
  FC = mpif90
  FFLAGS += -lmpi
 else
  FC = ifort
 endif
endif


### FX1, OpenMP uncheck, you have to use "gmake" instead of "make"
ifeq ($(ENVFLAGS),FX1)
 FC       = frt
 SRCS8   += mdp-uni.f
 FFLAGS   = -fw -X9 -Am $(OMPFLAGS) \
            -xzdistfunc,Gau -xtime_b -xshellspar -xfnf \
            -xsmmmod.xi,smmmod.eps
 FFLAGS  += -Kfast,ocl,preex
 # OPTFLAGS = -Kfast,ocl,preex
 ifeq ($(USEOMP),true) 
  FFLAGS += -KOMP
 endif
 ifeq ($(USEMPI),true)
  FC      = mpifrt
 endif
endif

### Mac Intel fortran
ifeq ($(ENVFLAGS),MacIfort)
 FC       = ifort
 IntelFortran = true
 SRCS8  += mdp-uni90.f
 FFLAGS  = -fpconstant -O3
 ifeq ($(USEOMP),true)
  FFLAGS  += -openmp
  LD = $(FC) -static-intel
 endif
 ifeq ($(USEMPI),true)
  FC       = mpif90 # CORRECT?
  FFLAGS  += -I/usr/local/lib -I/usr/local/include
  LDLIBS   = -lmpi_f90 -lmpi_f77 -lmpi -lm
  LDFLAGS += -L/usr/local/lib  -Wl,-commons,use_dylibs
 endif
endif

### Mac PGI Fortran
### PGI Fortran cannot accept CR+LF return code
### You have to change all return codes in input files, including xsdir.jnd
ifeq ($(ENVFLAGS),MacPGIfort)
 FC = pgfortran
 SRCS8  += mdp-uni90.f
 ifeq ($(DEBUG),true)
  FFLAGS = -O0 -g
 else
  FFLAGS = -O2 -Mipa=fast
 endif
 ifeq ($(USEOMP),true) 
  FFLAGS += -mp
 endif
 ifeq ($(USEMPI),true)
  FC = mpif90
  # FFLAGS += -Mmpi=mpich # for compiling w/ pgfortran
 endif
endif

### Mac gfortran (4.7 or 4.8)
ifeq ($(ENVFLAGS),MacGfort)
 OtherGfortran = true
 SRCS8    += mdp-uni90.f
 FC        = gfortran-mp-4.8
 FFLAGS    = -O0 -fdefault-double-8 -fdefault-real-8 -fdollar-ok
 ifeq ($(USEMPI),true)
  FFLAGS  +=   $(shell mpif90-openmpi-mp -showme:compile)
  FFLAGS  += -I$(shell mpif90-openmpi-mp -showme:incdirs)
  LDFLAGS  =   $(shell mpif90-openmpi-mp -showme:link)
  LDLIBS   = -lmpi_usempi -lmpi_mpifh -lmpi
 endif
 ifeq ($(USEOMP),true)
  FFLAGS += -fopenmp
 endif
endif

### Windows gfortran (4.7 or 4.8, MPI unchecked)
### gfortran 4.9 does not work!!
### You have to install "gfortran".
### Download site for GCC including gfortran for Windows
### (http://tdm-gcc.tdragon.net/download) Bundle installer is recommended.
### This package also has "mingw32-make" you can use make command for Windows.
ifeq ($(ENVFLAGS),WinGfort)
 OtherGfortran = true
 SRCS8   += mdp-win.f
 FC       = gfortran
 FFLAGS   = -O1 -fdefault-double-8 -fdefault-real-8 -fdollar-ok
 ifeq ($(USEMPI),true)
  # FFLAGS  += -I/usr/local/lib -I/usr/local/include
  # LDFLAGS  = -L/usr/local/lib -Wl,-commons,use_dylibs
  # LDLIBS   =  -lmpi_f90 -lmpi_f77 -lmpi -lm
 endif
 ifeq ($(USEOMP),true)
  FFLAGS += -fopenmp
 endif
endif

### Cygwin gfortran (4.7 or 4.8, MPI unchecked, Cygwin-32bit is not supported, use Cygwin-64bit.)
ifeq ($(ENVFLAGS),WinCygGfort)
 OtherGfortran = true
 SRCS8     += mdp-win.f
 FC         = gfortran
 FFLAGS     = -O0 -fdefault-double-8 -fdefault-real-8 -fdollar-ok
 ifeq ($(USEOMP),true)
  FFLAGS += -fopenmp
 endif
 ifeq ($(USEMPI),true)
  # FFLAGS  += -I/usr/local/lib -I/usr/local/include
  # LDFLAGS  = -L/usr/local/lib -Wl,-commons,use_dylibs
  # LDLIBS   =  -lmpi_f90 -lmpi_f77 -lmpi -lm
 else
  LDFLAGS  = -Wl,--stack,8388608
 endif
endif

#=======================================================================
# modules
#=======================================================================
SRCS0 = talmod.f \
	mmbankmod.f membankmod.f ggbankmod.f \
	ggmbankmod.f eventtalmod.f restalmod.f \
	gammod2.f gammod3.f gammod4.f gammod5.f gammod6.f \
	smm.f gammod1.f gammod.f ggm05mod.f \
	gammod-a.f gammod-b.f gammod-c.f gammod-d.f gammod-e.f \
	egs5mod.f \
	sumtallymod.f tetramod.f qmd_cood2_mod.f

#=======================================================================
# for machine dependent or user defined source and analysis
#=======================================================================
SRCS1 = \
	usrsors.f  usrmgf1.f  usrmgf3.f  anal-002.f \
	usrdfn1.f  usrdfn2.f subroutines.f90


#=======================================================================
# for param.inc
#=======================================================================
SRCS2 = \
	analyz.f   celimp.f   dataup.f   getflt.f   magtrs.f   \
	nreac.f    ovly12.f   ovly13.f   partrs.f   range.f    \
	read00.f   read01.f   read02.f   sors.f     talls00.f  \
	talls01.f  talls02.f  talls03.f  talls04.f  talls05.f  \
	talls06.f  talls07.f  tallsm1.f  tallsm2.f  tallsm3.f  \
	update.f   wrnt12.f   wrnt13.f   read03.f   marscg.f   \
	ggs00.f    ggs01.f    ggs02.f    ggs03.f    wrnt10.f   \
	geocntl.f  ggm01.f    ggm02.f    ggm03.f    ggm04.f    \
	ggm05.f    ggm06.f    ggm07.f    ggm08.f    ovly14.f   \
	ovly15.f   usrelst1.f usrelst2.f usrmgt1.f  usrmgt2.f  \
	talls08.f  statistic.f tallsm4.f itrminmax.f ggs04.f   \
	talls09.f

ifeq ($(ENVFLAGS),WinGfort)
 ifeq ($(USEOMP),true)
  SRCS2  += a-angel-winopenmp.f 
 else 
  SRCS2  += a-angel.f 
 endif
else 
  SRCS2  += a-angel.f 
endif


#=======================================================================
# for new package
#=======================================================================
SRCS3 = \
	main.f     dklos.f   ncasc.f     nelst.f    nevap.f    \
	sdml.f     gem.f     gemset.f    utl01.f    \
	utl02.f    jbook.f   masdis.f    atima01.f  atima02.f  \
	atima03.f  fismul.f  kurotama0.f usrtally.f incelf.f   \
	incelfin.f inclp.f   inclin.f    dwbain.f   dwbaD.f    \
	dwbaE.f    photnucl.f  aama.f    muoncap.f ompdump.f   \
	muonint.f  risource.f 

#=======================================================================
# for old package
#=======================================================================
SRCS4 = \
	bert.f     bertin.f   bert-bl0.f bert-bl1.f bert-bl2.f \
	utlnmtc.f  gamlib.f   erupin.f   erup.f     fissn.f    \
	isobert.f  isodat.f   randmc.f   energy.f   ndata01.f  \
	mars00.f   mars01.f   mars02.f   mars03.f   mars04.f

#=======================================================================
# for JAM
#=======================================================================
SRCS5 = \
	jamin.f    jam.f      jamdat.f   jamcoll.f  jamdec.f   \
	jamcross.f jampdf.f   jamsoft.f  jamhij.f   jamhard.f  \
	jambuu.f   jamana.f   pyjet.f    pythia.f   pysigh.f

#=======================================================================
# for JQMD
#=======================================================================
SRCS6 = \
	qmd00.f    qmdcoll.f  qmddflt.f  qmdgrnd.f  qmdinit.f   \
	qmdmfld.f                                               \
	qmd00_qmd-nr.f     qmdcoll_qmd-nr.f    qmdgrnd_qmd-nr.f \
	qmdmfld_qmd-nr.f

#=======================================================================
# for ANGEL except for utl03.f, a-func.f, a-utl00.f
#=======================================================================
SRCS7 = \
	utl03.f    a-func.f   a-utl00.f     \
	a-main0.f  a-main1.f  a-hsect.f  a-line.f   a-wtext.f

#=======================================================================
# for restart function and sumtally option
#=======================================================================
SRCS9 = \
	restart.f resutl.f \
	resttrack.f restcross.f restheat.f restdeposit.f restyield.f \
	restlet.f   restsed.f   restdpa.f  restproduct.f resttime.f  \
	restdeposit2.f reststar.f restpoint.f restadjnt.f restwwg.f  \
	restvlm.f \
	sumtally.f \
	sumtaltrack.f sumtaldeposit.f \
	sumtalcross.f sumtaldeposit2.f sumtaldpa.f sumtalheat.f \
        sumtallet.f   sumtalproduct.f  sumtalsed.f sumtalstar.f \
	sumtaltime.f  sumtalyield.f sumtalpoint.f sumtaladjnt.f \
	sumtalwwg.f   sumtalvlm.f

#======================================================================= 
# for EGS5
#======================================================================= 
SRCS10 = \
	egs5.f  egs5init.f      egs5pfpl.f      egs5pcoll.f     \
	egs5efpl.f      egs5ecoll.f     egs5ede.f       egs5annih.f     \
	egs2phits.f     egs5esteps0.f	egs5edxde.f	egs5init2.f	\
	egs5elast.f     egs5ededx.f   egs_elmgfd.f  etsmode.f

#======================================================================= 
# for BITMAP
#======================================================================= 
SRCS11 = \
	bitmap_main.f bitmap_a-main0.f bitmap_a_angel.f bitmap_util.f  \
	vtk_main.f vtk_gshow.f vtk_util.f

SRCS = $(SRCS0) $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) \
       $(SRCS5) $(SRCS6) $(SRCS7) $(SRCS8) $(SRCS9) \
       $(SRCS10) $(SRCS11)

OBJS = $(SRCS:.f=.o)

LD = $(LINK.f)
ifeq ($(ENVFLAGS),MacIfort)
#  LD = $(FC) -static-intel $(LDFLAGS)
  LD = $(FC) -static-intel $(FFLAGS)
endif
#LD = $(FC)

$(TARGET) : $(OBJS)
	$(LD) -o $@ $^
# According to the description [10.2 Catalogue of Built-In Rules]
# for 'Linking a single object file' in the GNU make manual,
# "... when there is no object file whose  name derives from the
# executable file name, you must write an explicit recipe for linking."
# though there're some built-in rules...

# .f.o:
#	$(FC) -c $(FFLAGS) $(INCLUDES) $(OPTFLAGS) $*.f $(LIBS)
# For 'Compiling Fortran and Ratfor programs' there's no need
# to write an explicit rule, because the following rules suffice.
##### The GNU make built-in rules
# %.o: %.f
# #  recipe to execute (built-in):
#         $(COMPILE.f) $(OUTPUT_OPTION) $<
# # default
# COMPILE.f = $(FC) $(FFLAGS) $(TARGET_ARCH) -c

### default rule for a module (nothing done, just a dependency)
# c.f. http://lagrange.mechse.illinois.edu/f90_mod_deps/
#      http://qiita.com/chirimen/items/af8479d8c0c7cf545b1e
%.mod : %.f %o
	@:

### clean-up and recreate the file which describes dependencies
#     for all fortran source files w/ extension '.f'.
#     Note the use of 'makedepfort' with option '-m', which removes
#     the dependency on 'mpif.h'.
DEPFILE = make.depend
include $(DEPFILE)
ifdef DEVEL
 depend $(DEPFILE):
	@rm -f $(DEPFILE)
	@makedepfort *.f > $(DEPFILE)
endif

##### Special (explicit) compile rules for some object files.
gammod.o gammod1.o gammod-a.o gammod-b.o gammod-c.o gammod-d.o gammod-e.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 $*.f

ifeq ($(DEBUG),true)
 usrtally.o:
 ifeq ($(ENVFLAGS),LinIfort)
	$(FC) -c $(FFLAGS) -check bounds -gen-interfaces -warn interfaces $*.f
 endif
 ifeq ($(ENVFLAGS),LinPGIfort)
	$(FC) -c $(FFLAGS) -Mbounds $*.f
 endif
endif

ifeq ($(OtherGfortran),true)
  read00.o read03.o risource.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 $*.f
endif
ifeq ($(IntelFortran),true)
  gammod4.o gammod5.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 $*.f
  gammod3.o gammod6.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 -real_size 64 $*.f
  restdeposit.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 $*.f
  sumtaltrack.o sumtaldeposit.o sumtalcross.o sumtaldeposit2.o \
  sumtaldpa.o sumtalheat.o sumtallet.o sumtalproduct.o sumtalsed.o \
  sumtalstar.o sumtaltime.o sumtalyield.o sumtalpoint.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 $*.f
  ifeq ($(USEOMP),true)
    aama.o:
	$(FC) -c $(filter-out -O%,$(FFLAGS)) -O0 $*.f
  endif
endif

clean:
	@$(RM) -f $(OBJS) *.mod
ifdef DEVEL
	@$(RM) -f $(DEPFILE)
endif

.PHONY: depend
