TARGET=robots

SOURCE_ALT = alt/UltraSonicSensor.alt\
	alt/TouchSensor.alt\
	alt/SoundSensor.alt\
	alt/Motor.alt\
	alt/LightSensor.alt\
	alt/BTMaster.alt\

SOURCE_ACHECK = acheck/UltraSonicSensor.acheck\
	acheck/TouchSensor.acheck\
	acheck/SoundSensor.acheck\
	acheck/Motor.acheck\
	acheck/LightSensor.acheck\
	acheck/BTMaster.acheck\


GENERATED_RES = UltraSonicSensor.res\
	TouchSensor.res\
	SoundSensor.res\
	Motor.res\
	LightSensor.res\
	BTMaster.res\

GENERATED_PROP = UltraSonicSensor.prop\
	TouchSensor.prop\
	SoundSensor.prop\
	Motor.prop\
	LightSensor.prop\
	BTMaster.prop\

GENERATED_EPS = UltraSonicSensor.eps\
	TouchSensor.eps\
	SoundSensor.eps\
	Motor.eps\
	LightSensor.eps\
	BTMaster.eps\

GENERATED_PDF = UltraSonicSensor.pdf\
	TouchSensor.pdf\
	SoundSensor.pdf\
	Motor.pdf\
	LightSensor.pdf\
	BTMaster.pdf\

# SOURCE_TEX = $(TARGET).tex\

GRAPHS = UltraSonicSensor.eps\
	TouchSensor.eps\
	SoundSensor.eps\
	Motor.eps\
	LightSensor.eps\
	BTMaster.eps\

SUBDIRS = acheck alt

# all: $(TARGET).ps.gz
all: $(TARGET).res

clean:
	for d in $(SUBDIRS); do \
		$(MAKE) -C $$d $@ || exit 1;\
	done
	for d in $(GENERATED_RES); do \
		if [ -f $$d ]; then \
			rm $$d; \
		fi \
	done
	for d in $(GENERATED_PROP); do \
		if [ -f $$d ]; then \
			rm $$d; \
		fi \
	done
	rm -f *.dvi *.log *.aux *.toc *.bbl *.blg *~ core *.dot *#

cleanAll: clean
	rm -f *.eps *.prop *.res $(TARGET).alt $(TARGET).acheck $(TARGET).ps.gz

$(TARGET).alt: $(SOURCE_ALT)
	rm -f $(TARGET).alt
	for d in $(SOURCE_ALT); do \
		echo "\n" >> $(TARGET).alt;\
		cat $$d >> $(TARGET).alt;\
	done

$(TARGET).acheck: $(SOURCE_ACHECK)
	rm -f $(TARGET).acheck
	for d in $(SOURCE_ACHECK); do \
		echo "\n" >> $(TARGET).acheck;\
		cat $$d >> $(TARGET).acheck;\
	done

$(TARGET).res: $(TARGET).alt $(TARGET).acheck
	acheck $(TARGET).alt $(TARGET).acheck
	rm -f $(TARGET).res
	for d in $(GENERATED_RES); do \
		echo "\n$$d" >> $(TARGET).res;\
		cat $$d >> $(TARGET).res;\
	done
	rm -f $(TARGET).prop
	for d in $(GENERATED_PROP); do \
		echo "\n$$d" >> $(TARGET).prop;\
		cat $$d >> $(TARGET).prop;\
	done
	make $(GRAPHS)
# 	for d in $(GENERATED_EPS); do \
# 		epstopdf $$d;\
# 	done
# 	pdftk *.pdf cat output $(TARGET)_eps.pdf



# $(TARGET).ps.gz: $(TARGET).res $(SOURCE_TEX)
# 	latex $(TARGET) && latex $(TARGET) && dvips $(TARGET).dvi -o && gzip -f $(TARGET).ps

.SUFFIXES: .dot .eps

.dot.eps: $*.dot
	dot -Tps $*.dot -o $*.eps
