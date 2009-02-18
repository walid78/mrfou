TARGET=robot

all: $(TARGET).alt
all: Direction.res UltraSonicSensor.res TouchSensor.res SoundLightSensor.res DummySensor.res ServoMotor.res MasterRobot.res SlaveRobot.res System.res
all: Direction.eps UltraSonicSensor.eps TouchSensor.eps SoundLightSensor.eps DummySensor.eps ServoMotor.eps MasterRobot.eps SlaveRobot.eps System.eps

clean:
	rm -f *.dvi *.log *.aux *~ core Alt/*~

cleanAll: clean
	rm -f *.eps *.dot *.prop *.res *.diff 
	rm -f $(TARGET).alt

$(TARGET).alt: Alt/*.alt
	cat Alt/ServoMotor.alt > $(TARGET).alt
	cat Alt/UltraSonicSensor.alt >> $(TARGET).alt
	cat Alt/TouchSensor.alt >> $(TARGET).alt
	cat Alt/SoundLightSensor.alt >> $(TARGET).alt
	cat Alt/DummySensor.alt >> $(TARGET).alt
	cat Alt/Direction.alt >> $(TARGET).alt
	cat Alt/IdleMasterController.alt >> $(TARGET).alt
	cat Alt/IdleSlaveController.alt >> $(TARGET).alt
	cat Alt/MissionController.alt >> $(TARGET).alt
	cat Alt/MasterRobot.alt >> $(TARGET).alt
	cat Alt/SlaveRobot.alt >> $(TARGET).alt
	cat Alt/System.alt >> $(TARGET).alt

.SUFFIXES: .dot .eps .res .spe .alt

.dot.eps: $*.dot
	dot -Tps $*.dot -o $*.eps

.spe.res: $(TARGET).alt $*.spe
	acheck $(TARGET).alt $*.spe

.spe.dot: $(TARGET).alt $*.spe
	acheck $(TARGET).alt $*.spe
