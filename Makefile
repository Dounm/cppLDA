#TODO: optimize this Makefile
CXX=g++
CXXFLAGS=-c -Wall -pg
#CXXFLAGS=-c -Wall -Werror -g
LDFLAGS= 
DEP_INCPATH=-I. -I./dlog

all : lda

clean :
	rm -f *.o
	rm -f lda
	rm -f DLOG*

lda : lda.o lda_model.o dataset.o util.o document.o dlog.o dlog_util.o
	$(CXX) $(LDFLAGS)  lda.o lda_model.o dataset.o util.o document.o dlog.o dlog_util.o -o lda

lda.o : lda.cpp lda_model.h dataset.h dlog/dlog.h util.h document.h dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) lda.cpp 

lda_model.o : lda_model.cpp lda_model.h dataset.h dlog/dlog.h util.h document.h dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) lda_model.cpp 

dataset.o : dataset.cpp dataset.h dlog/dlog.h util.h document.h  dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) dataset.cpp 

document.o : document.cpp dlog/dlog.h util.h document.h dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) document.cpp 

util.o : util.cpp dlog/dlog.h util.h dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) util.cpp 

dlog.o : dlog/dlog.cpp dlog/dlog.h dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) dlog/dlog.cpp

dlog_util.o : dlog/util.cpp dlog/util.h
	$(CXX) $(CXXFLAGS) $(DEP_INCPATH) dlog/util.cpp -o dlog_util.o
