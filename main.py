import serial
import time

aduinoPort = 'COM4' # Desktop
# aduinoPort = '/dev/ttyACM0' # Pi

if __name__ == '__main__': 

    ser = serial.Serial(aduinoPort, 9600, timeout=1)
    ser.reset_input_buffer()

    # write test data so the system won't fail in the first run
    ser.write(b"startUp\n")
    ser.readline().decode('utf-8').rstrip()
    print("Serial connection is ready.")




    def readAnalogArduinoPin(pinNumber: int, timeOut: float, attempts: int):
        pinSector = 'A'
        rData = 0 # restet data
        flag = False # indicates if data has been read successfully (flase=unsuccessful)
        for i in range(0, attempts):
            ser.write(bytes(pinSector + str(pinNumber) + "\n", 'utf-8')) # requesting data from pin
            line = ser.readline().decode('utf-8').rstrip() # recieving pin + data

            # spliting up recieved data:
            rPinSector = line[0] # get pin sector from the first char
            rPinNumber = int(line[1:3]) # get pin number from second and third char

            if((rPinSector == pinSector) & (rPinNumber == pinNumber)): # checking, if data comes from the right pin
                rData = int(line[3:7]) # get data from analog pin
                flag = True # data has been read successfully
                break # stop loop, because data has been read successfully

            time.sleep(timeOut) # delay, until next read
        returnData = [rData, flag, i+1] # defining return data
        return returnData


    def writeDigitalArduinoPin (pinNumber: int, writingType: str, data: int):
        pinSector = 'D'
        data = str(data)
        if (writingType == 'a'): # formate data with 0, so it fits in the syntax
            for i in range(len(data), 3): 
                data = "0" + data
        sendingData = bytes(pinSector + str(pinNumber) + writingType + data + "\n", 'utf-8') # put together syntax
        ser.write(sendingData) # write data
    

    # Example:
    print(readAnalogArduinoPin(1, 0.1, 4))

    writeDigitalArduinoPin(53, "d", 1)
    