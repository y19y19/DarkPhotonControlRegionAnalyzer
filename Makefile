SDIR := src
ODIR := obj
IDIR := interface
BDIR := bin

CC = g++ -lTMVA
CFLAGS = `root-config --cflags --libs` -I $(IDIR)



EXE := $(BDIR)/main
SRC := $(wildcard $(SDIR)/*.C)
OBJ := $(SRC:$(SDIR)/%.C=$(ODIR)/%.o)

.PHONY: all clean

#main: EventLoop.o EventsAnalysisMain.o EventsAnalysisFunctions.o PUWeightProducer.o HEPMathTools.o
#	$(CC) $(CFLAGS) -o main EventLoop.o EventsAnalysisMain.o EventsAnalysisFunctions.o PUWeightProducer.o HEPMathTools.o

#EventLoop.o: src/EventLoop.C 
#	$(CC) $(CFLAGS) -c src/EventLoop.C 

#EventsAnalysisMain.o: src/EventsAnalysisMain.C
#	$(CC) $(CFLAGS) -c src/EventsAnalysisMain.C

#EventsAnalysisFunctions.o: src/EventsAnalysisFunctions.C
#	$(CC) $(CFLAGS) -c src/EventsAnalysisFunctions.C

#PUWeightProducer.o: src/PUWeightProducer.C 
#	$(CC) $(CFLAGS) -c src/PUWeightProducer.C 

#HEPMathTools.o: src/HEPMathTools.C 
#	$(CC) $(CFLAGS) -c src/HEPMathTools.C

#all: $(EXE)
#	@echo $(EXE)
#	@echo $(SRC)
#	@echo $(OBJ)


$(EXE): $(OBJ) | $(BDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(ODIR)/%.o: $(SDIR)/%.C | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin and obj folder 
$(BDIR) $(ODIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BDIR) $(ODIR)

-include $(OBJ:.o=.d)
