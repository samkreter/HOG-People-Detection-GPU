import matplotlib.pyplot as plt
import numpy as np
import pca

imgSizes = [ 2, 4, 8, 10, 20]
Ts = [ 1, 32, 128, 256, 512, 1024]

float_formatter = lambda x: "%.5f" % x
np.set_printoptions(formatter={'float_kind':float_formatter})


def takeAverageOfFile(filenameIn, filenameOut):
    '''Load a csv and take the average of the sections
         with the same value for first and second columns'''

    data = np.genfromtxt(filenameIn,delimiter=',')
    avgData = []

    for size in imgSizes:
        for t in Ts:
            temp = data[np.logical_and(data[:,0] == t,data[:,1] == size)]
            N = temp[:,0].size
            tempSum = [np.sum(temp[:,i])/N for i in range(temp[0].size)]
            avgData.append(tempSum)
    finalData = np.array(avgData)
    np.savetxt(filenameOut,finalData,delimiter=",",fmt='%.5f')
    return finalData

def getSumTimes(data):
    return np.sum(data,axis=0)

def getSumTimesFile():
    data = np.genfromtxt("times.csv",delimiter=',')
    return np.sum(data,axis=0)

def getParalleSpeedUp(data):
    for i in range(data[:,0].size):
        data[i,3] = data[i,5] / data[i,2]
    return data

def plotPicSizeValues(data):
    cs = ['r','b','g','y','k']
    for c,picSize in zip(cs,picSizes):
        plt.plot(data[data[:,1] == picSize,0], data[data[:,1] == picSize,2], c+'o-',label=str(picSize)+" Image Size")
    plt.xlabel('Number of Threads per Block')
    plt.ylabel('Time to Process')
    plt.grid(True)
    plt.legend()
    fig1 = plt.gcf()
    fig1.savefig('kValue.png')
    plt.show()

def plotTValues(data):
    cs = ['r','b','g','y','k','m']
    for c,t in zip(cs,Ts):
        plt.plot(data[data[:,0] == t,1], data[data[:,0] == t,2], c+'o-',label=str(t)+" Threads per Block")

    plt.xlabel('Size of the Picture')
    plt.ylabel('Time to Process')
    plt.grid(True)
    plt.legend()
    fig2 = plt.gcf()
    fig2.savefig('tValue.png')
    plt.show()



def getLabels(data):
    col1 = data[:,0]
    col2 = data[:,1]

    y = np.column_stack((col1,col2))
    X = data[:,2:]

    return X,y


if __name__ == '__main__':
    test = takeAverageOfFile("times.csv","averagedData.csv")
    # test2 = test[test[:,2].argsort()]
    # getParalleSpeedUp(test)
    # final = test[test[:,2].argsort()]
    # np.savetxt("topValuesPar.csv",final[:,:4],delimiter=",",fmt='%.5f')
    # plotPValues(test)
    # plotkValues(test)
    #print(getSumTimes(test))
    #test1 = getParalleSpeedUp(test) * 100