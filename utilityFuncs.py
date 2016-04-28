import matplotlib.pyplot as plt
import numpy as np


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



def getSumTimesFile():
    data = np.genfromtxt("times.csv",delimiter=',')
    return np.sum(data,axis=0)

def plotSizeTime(data):
    x = [ i for i in range(len(imgSizes))]
    sizes = ["550x366","1100x732","2200x1464","2750x1830","5500x3660"]
    gpu = []
    cpu = []
    for line in data[data[:,0] == 128]:
        gpu.append(line[5])
        cpu.append(line[4])
    plt.plot(x,gpu,'go-',label="GPU")
    plt.plot(x,cpu,'bo-',label="CPU")
    plt.title("With Threads per Block set at 128")
    plt.xticks(x,sizes)
    plt.xlim([0,5])
    plt.ylim([0,6.5])
    plt.xlabel('Image Sizes')
    plt.ylabel('Time to Compute (s)')
    plt.grid(True)
    plt.legend(loc=4)
    fig1 = plt.gcf()
    fig1.savefig('SizeTime.png')
    plt.show()

def plotThreadTime(data):
    gpu = []
    cpu = []
    for line in data[data[:,1] == 10]:
        gpu.append(line[5])
        cpu.append(line[4])
    plt.plot(Ts,gpu,'go-',label="GPU")
    plt.plot(Ts,cpu,'bo-',label="CPU")
    plt.title("With 2750x1830 Set Image")
    plt.xticks(Ts,Ts)
    plt.xlabel('Number of Threads per Block')
    plt.ylabel('Time to Compute (s)')
    plt.xlim([-1,1050])
    plt.grid(True)
    plt.legend()
    # fig2 = plt.gcf()
    # fig2.savefig('ThreadTime.png')
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
    plotThreadTime(test)
    #plotSizeTime(test)
    # test2 = test[test[:,2].argsort()]
    # getParalleSpeedUp(test)
    # final = test[test[:,2].argsort()]
    # np.savetxt("topValuesPar.csv",final[:,:4],delimiter=",",fmt='%.5f')
    # plotPValues(test)
    # plotkValues(test)
    #print(getSumTimes(test))
    #test1 = getParalleSpeedUp(test) * 100