
import keras
import numpy as np
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD
from keras.utils import np_utils
from keras.optimizers import Adam
import pandas as pd
import csv #csvファイルの読みこみ

def LoadData(DataPath,Nrows=None):
    df=pd.read_csv(DataPath,sep=',')#データをロードする関数。dfを戻り値にする
    return df

def FeatEng(df):
    
    df=df.sample(frac=1)
    df=df.values
    dfX=df[0:2500000,0:10]
    dfY=df[0:2500000,19]
   # x_hit = (dfX > 0).sum(axis=1)#何層当たったかをこのコラムに入れる
   # dfX=np.c_[dfX,x_hit]
   # dfX = (dfX - dfX.mean())/dfX.std(ddof=0)#標準化
    ymean = dfY.mean()
    ystd = dfY.std(ddof=0)
  #  dfY = (dfY - ymean)/ystd#正解値の方も標準化
    
    return dfX,dfY,ystd,ymean


def split(dfX,dfY):
    x_train=dfX[0:2000000,0:10]
    x_test=dfX[2000000:2500000,0:10]
    y_train=dfY[0:2000000]
    y_test=dfY[2000000:2500000]
    
    return x_train,y_train,x_test,y_test






if __name__=="__main__":
    
    df = LoadData("output1.csv", Nrows=None)
    print(df)
    dfX,dfY, ystd, ymean = FeatEng(df)
    x_train,y_train,x_test,y_test=split(dfX,dfY)
    print(x_train)
    print(y_test)

    model = Sequential()
    model.add(Dense(3,input_dim=10))
    model.add(Activation('relu'))

    
#    model.add(Dense(3))
#    model.add(Activation('relu'))

    model.add(Dense(1))

    model.compile(loss='mean_squared_error',optimizer=Adam(lr=0.001,beta_1=0.9,beta_2=0.999,epsilon=None,decay=0.0,amsgrad=False),metrics=['mae'])

    epochs=50
    batch_size=50

    result=model.fit(x_train,y_train,epochs=epochs,batch_size=batch_size,validation_data=(x_test,y_test))


    loss_and_metrics=model.evaluate(x_test,y_test)
    print(loss_and_metrics)



    score=model.evaluate(x_test,y_test,verbose=0)

    print(result.history)
    mae=result.history['mean_absolute_error']#学習用データの精度
    loss=result.history['loss']#学習用データの損失関数
    val_mae=result.history['val_mean_absolute_error']#検証用データの精度
    val_loss=result.history['val_loss']#検証用データの損失関数
    

    #print(acc)#
    #print(np.c_[acc,loss,val_acc,val_loss])#配列の結合

    path_w3 ='test3.csv'
    path_w4 ='correct_output.txt'
    history=np.savetxt(path_w3,np.c_[mae,loss,val_mae,val_loss],delimiter=",",fmt="%s",header='mae,loss,va_mae,val_loss')
    
    predict=model.predict(x_test)
    connect=np.c_[y_test,predict]
    correct_output=np.savetxt(path_w4,connect,delimiter=" ",fmt="%s")

    #path_w1 ='/mnt/test1.csv'
    #path_w2 ='/mnt/c/Users/komori/Desktop/test2.csv'
    
    #y_test=np.savetxt(path_w1,y_test,delimiter=",",fmt="%s")
    #predict=np.savetxt(path_w2,predict,delimiter=",",fmt="%s")
    # print(y_test)
    
    #重みを保存する
    json_string=model.to_json()
    yaml_string=model.to_yaml()
    model.save_weights('weihgts.h5');
    open('model.json','w').write(json_string)
    
