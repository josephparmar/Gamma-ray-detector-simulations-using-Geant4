
import numpy as np
import matplotlib.pyplot as plt
import sys


#Matplotlib setup
plt.style.use('classic')
fig, axes = plt.subplots(1, 2)
ax1, ax2 = axes

fig.figure.set_size_inches(12, 6)
fig.suptitle("Energy spectrum of 10MeV gamma rays detected by an NaI scintillator.", fontsize=16)

ax2.set_yscale("log")

#Loads the data from the file at location filename. returns an array of energy values as floats
def LoadData(filename:str):
    sData = np.loadtxt(filename, comments="#", delimiter=" ", unpack=False, dtype=str, usecols=2, max_rows=10000000000)
    fData = sData.astype(np.float64)
    return fData

#Defines the function to bin the data based on a user selected number of bins. Returns the counts in each bin, and the bin edges.
def binData(data):
    binNumber = int(np.sqrt(len(data)))
    binsEdges = np.linspace(0, max(data), binNumber+1)
    hist, bins = np.histogram(data, bins=binsEdges)

    #normalises the values (So results can be compared with each other as bin count refers to proportion of total measurements)
    total =0
    for i in hist:
        total += i
    hist_norm=[]
    for i in hist:
        hist_norm.append(i/total)

    return hist_norm, bins

#Plots the histogram.
def plotHist(counts, bins):

    ax1.stairs(counts, bins, fill=False)
    ax1.set_ylabel("Proportion of detections at energy E")
    ax1.set_xlabel("Energy E (MeV)")
    ax1.grid(True)
    ax1.set_xlim(4, max(bins)*1.05)

    
    ax2.stairs(counts, bins, fill=False, color="red")
    ax2.set_ylabel("Log(Proportion of detections at energy E)")
    ax2.set_xlabel("Energy E (MeV)")
    ax2.grid(True)
    ax2.set_xlim(4, max(bins)*1.05)
    
def plotLine(counts, bins):
    ax1.plot(bins[:-1], counts, linewidth=1)
    ax1.set_ylabel("Proportion of detections at energy E")
    ax1.set_xlabel("Energy E (MeV)")
    ax1.grid(True)
    ax1.set_xlim(4, max(bins)*1.05)

    logCount = []
    for i in counts:
        logCount.append(np.log(i))
    ax2.plot(bins[:-1], logCount, linewidth=1)
    ax2.set_ylabel("Log(Proportion of detections at energy E)")
    ax2.set_xlabel("Energy E (MeV)")
    ax2.grid(True)
    ax2.set_xlim(4, max(bins)*1.05)

def main(filename):
    raw_data = LoadData(filename)
    data=[]
    for i in raw_data:
        if i > 0:
            data.append(i)


    histogram, totalBins= binData(data)
    print(totalBins)
    plotHist(histogram, totalBins)
    #plotLine(histogram, totalBins)
    plt.show()
    
if __name__ == "__main__":
    arguments = sys.argv
    main(arguments[1])