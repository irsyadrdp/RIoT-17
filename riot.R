#download & load rjson library

library(rjson)
library(gradDescent)
setwd("Z:/TEMP FD/RIoT Hackathon 2017/riot")
URL <- "http://staging.atilze.com/api/riot/9181e6a2"
data <- fromJSON(paste(readLines(URL), collapse=""))



###Create model
dataSet<-read.table(file="data-training.csv", sep=",", header=TRUE)

featureScalingResult<-minmaxScaling(dataSet)
splittedDataSet<-splitData(featureScalingResult$scaledDataSet)
model<-GD(splittedDataSet$dataTrain)



###create matrix
sensingData<-matrix(ncol=4)
colnames(sensingData)<-c("Temperature","AccelX","AccelY","AccelZ")
sensingData<-rbind(sensingData, c(32,-1.5,0.5,1))  
###delete 1st row of matrix
#sensingData<-sensingData[-1,]



valueTemp<-dataSet[nrow(dataSet),1];
valueAccelX<-dataSet[nrow(dataSet),2]
valueAccely<-dataSet[nrow(dataSet),3]
valueAccelz<-dataSet[nrow(dataSet),4]




scrapData<-function(){
    repeat{
        name<-data$deviceData[[2]]$Name
        value<-data$deviceData[[2]]$Value
        
        if(name=="temperature"){
            sensingData<-rbind(sensingData, c(value,valueAccelX,valueAccely,valueAccelz))        
        }
        
        if(name=="accelerometer"){
            sensingData<-rbind(sensingData, c(valueTemp,value,value,value))
        }
        
        
        sensingData2<-data.frame(sensingData)
        write.csv(sensingData2, file="C:\\Users\\user\\Desktop\\riot\\datasets.csv", row.names=FALSE)
    }    
    
    return (sensingData2)
}

scrapData()
dataTest<-read.table(file="datasets.csv", sep=",", header=TRUE)

dataTest<-dataTest[-1,]
prediction<-prediction(model,dataTest)

datta<-read.table(file="33.csv", sep=",", header=TRUE)
datta


plot(dataSet[,1],type="h")
par(new=TRUE)
plot(dataSet[,2],type="l", col="red")
par(new=TRUE)
plot(dataSet[,5],type="l", col="blue")
