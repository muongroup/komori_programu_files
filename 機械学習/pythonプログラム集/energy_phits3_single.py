
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

#/home/komori/python_practice/machine_learning_data_set/
data1 = pd.read_csv('data1_5_1.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
data2 = pd.read_csv('data1_5_2.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
data3 = pd.read_csv('data1_5_3.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 

#print(type(data))
data1=data1.sample(frac=1)#データのシャッフル
data1=data1.values#pandasをnumpyに変更
data2=data2.sample(frac=1)#データのシャッフル
data2=data2.values#pandasをnumpyに変更
data3=data3.sample(frac=1)#データのシャッフル
data3=data3.values#pandasをnumpyに変更

data=np.r_[data1,data2,data3]
#print(type(data))
print(np.shape(data))
#print(data[4])

#学習用のデータ
x_train=data[0:2500000,0:10]#配列の0列目からシンチの付与エネルギー情報が入っている
#x_train=x_train.round(1)
#print(np.shape(x_train))
#print(x_train)
y_train=data[0:2500000,19]#入射エネルギー情報をとってくる
#y_train=y_train.round(1)
print(y_train)
#y_train=np.ceil(y_train)
#y_train=y_train-1
print(y_train)
#y_train/=300

#print(np.shape(y_train))
#print(np.round(y_train))
#print(y_train)

#テスト用のデータ
x_test=data[2500000:2900000,0:10]
#print(np.shape(x_test))
#print(x_test)
#x_test=x_test.round(1)
y_test=data[2500000:2900000,19]
#y_test=y_test.round(1)
#print(np.shape(y_test))
#print(y_test)
#y_test=np.ceil(y_test)
#y_test=y_test-1
#y_test/=300

#y_train=np.trunc(y_train)
#y_test=np.trunc(y_test)
#y_train=np.arange(y_train)
#y_test=y_test.flatten()
print(y_test)
print(np.ndim(y_train))
print(np.shape(y_train))





model = Sequential()
model.add(Dense(7,input_dim=10))
model.add(Activation('relu'))


#model.add(Dense(1000))
#model.add(Activation('relu'))

model.add(Dense(3))
model.add(Activation('relu'))

#model.add(Dense(100))
#model.add(Activation('relu'))


model.add(Dense(1))
#model.add(Activation('relu'))




#model.compile(loss='binary_crossentropy',optimizer=SGD(lr=0.01),metrics=['mae'])
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

history=np.savetxt(path_w3,np.c_[mae,loss,val_mae,val_loss],delimiter=",",fmt="%s",header='mae,loss,va_mae,val_loss')

predict=model.predict(x_test)
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


"""
#一つ一つの値を評価させている
xx_test=data[910000,0:3]
xx_test=xx_test.reshape(1,3)
print(np.shape(xx_test))

yy_test=data[910000,6]
yy_test=(yy_test-1)
yy_test=np.trunc(yy_test)
print('xx_test',xx_test)
print(yy_test)
yy_test=np_utils.to_categorical(yy_test,100)#ワンホット化
yy_test=yy_test.reshape(1,100)
print(np.shape(yy_test))
#print('xx_test',xx_test)
print('yy_test',yy_test)
model.evaluate(xx_test,yy_test,verbose=0)

predict=model.predict(xx_test)
print(predict)


#ファイル書き出しについて
path_w1 ='/mnt/c/Users/komori/Desktop/test1.csv'
path_w2 ='/mnt/c/Users/komori/Desktop/test2.csv'
#with open(path_w,mode='w') as f:
yy_test=np.savetxt(path_w1,yy_test,delimiter=",",fmt="%s")
predict=np.savetxt(path_w2,predict,delimiter=",",fmt="%s")
#    f.write(yy_test)


"""
