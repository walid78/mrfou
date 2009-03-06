TARGET=robots

SOURCE_ALT = alt/UltraSonicSensor.alt\
	alt/TouchSensor.alt\
	alt/SoundSensor.alt\
	alt/Motor.alt\
	alt/LightSensor.alt\

SOURCE_ACHECK = acheck/UltraSonicSensor.acheck\
	acheck/TouchSensor.acheck\
	acheck/SoundSensor.acheck\
	acheck/Motor.acheck\
	acheck/LightSensor.acheck\


GENERATED_RES = UltraSonicSensor.res\
	TouchSensor.res\
	SoundSensor.res\
	Motor.res\
	LightSensor.res\

# SOURCE_TEX = $(TARGET).tex\

GRAPHS = UltraSonicSensor.eps\
	TouchSensor.eps\
	SoundSensor.eps\
	Motor.eps\
	LightSensor.eps\

SUBDIRS = acheck alt

# all: $(TARGET).ps.gz
all: $(TARGET).res

clean:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d $@ || exit 1;\
	done
	rm -f *.dvi *.log *.aux *.toc *.bbl *.blg *~ core *.dot

cleanAll: clean
	rm -f *.eps *.prop *.res $(TARGET).alt $(TARGET).acheck $(TARGET).ps.gz

$(TARGET).alt: $(SOURCE_ALT)
	rm -f $(TARGET).alt
	for d in $(SOURCE_ALT); do \
		echo "\n" >> $(TARGET).res;\
		cat $$d >> $(TARGET).alt;\
	done

$(TARGET).acheck: $(SOURCE_ACHECK)
	rm -f $(TARGET).acheck
	for d in $(SOURCE_ACHECK); do \
		echo "\n" >> $(TARGET).res;\
		cat $$d >> $(TARGET).acheck;\
	done

$(TARGET).res: $(TARGET).alt $(TARGET).acheck
	acheck $(TARGET).alt $(TARGET).acheck
	for d in $(GENERATED_RES); do \
		echo "\n$$d" >> $(TARGET).res;\
		cat $$d >> $(TARGET).res;\
	done
	make $(GRAPHS)

# $(TARGET).ps.gz: $(TARGET).res $(SOURCE_TEX)
# 	latex $(TARGET) && latex $(TARGET) && dvips $(TARGET).dvi -o && gzip -f $(TARGET).ps

.SUFFIXES: .dot .eps

.dot.eps: $*.dot
	dot -Tps $*.dot -o $*.eps
