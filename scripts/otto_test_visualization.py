import sys
import matplotlib.pyplot as plt
import csv

x = []
wormhole = []
chorus = []

with open(sys.argv[1],'r') as csvfile:
    benchmarks = csv.reader(csvfile, delimiter=',')
    for i in [0,1,2,3]:
        next(benchmarks, None)
        
    for row in benchmarks:
        #Extracts numbers from string
        numbers = [int(s) for s in row[0].split() if s.isdigit()]
        #Take first one. Hopefully the buffer size
        if numbers[0] not in x:
            x.append(numbers[0])

        if 'Wormhole::process' in row[0].split():
            wormhole.append(float(row[2]))
        if 'Chorus::process' in row[0].split():
            chorus.append(float(row[2]))

plt.plot(x, wormhole, label='Wormhole')
plt.plot(x, chorus, label='Chorus')
plt.xscale('log', basex = 2)
plt.xlabel('Buffer size')
plt.ylabel('Time per sample')
plt.title('Engine Benchmarks')
plt.legend()
plt.show()
