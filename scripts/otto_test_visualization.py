import sys
import matplotlib.pyplot as plt
import csv

x = []
wormhole = []
chorus = []
audio = []
audio_x = []

with open(sys.argv[1],'r') as csvfile:
    benchmarks = csv.reader(csvfile, delimiter=',')
    next(benchmarks, None)
    for row in benchmarks:
        #Extracts numbers from string
        numbers = [int(s) for s in row[0].split() if s.isdigit()]
        #Take first one. Hopefully the buffer size
        if 'AudioManager::process,' in row[0].split():
            audio.append(float(row[2]))
            if numbers[0] not in audio_x:
                audio_x.append(numbers[0])
        else:
          if numbers[0] not in x:
              x.append(numbers[0])

          if 'Wormhole::process' in row[0].split():
              wormhole.append(float(row[2]))
          if 'Chorus::process' in row[0].split():
              chorus.append(float(row[2]))

plt.plot(x, wormhole, label='Wormhole')
plt.plot(x, chorus, label='Chorus')
plt.plot(audio_x, audio, label='Application')
plt.xscale('log', basex = 2)
plt.xlabel('Buffer size')
plt.ylabel('Time per sample')
plt.title('Engine Benchmarks')
plt.legend()
plt.show()
