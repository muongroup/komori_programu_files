import keras
import numpy as np
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD
from keras.utils import np_utils
import pandas as pd
import csv #csvファイルの読みこみ

#/home/komori/python_practice/machine_learning_data_set/
data = pd.read_csv('/home/komori/python_practice/machine_learning_data_set/data1_1.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 

#print(type(data))

data=data.values#pandasをnumpyに変更



#print(type(data))
#print(np.shape(data))
#print(data[4])

#学習用のデータ
x_train=data[0:800000,0:3]#配列の0列目からシンチの付与エネルギー情報が入っている
#print(np.shape(x_train))
#print(x_train)
y_train=data[0:800000,6]#入射エネルギー情報をとってくる
print(y_train)
y_train=y_train-1

print(y_train)
y_train/=10


#print(np.shape(y_train))
#print(np.round(y_train))
print(y_train)

#テスト用のデータ
x_test=data[800000:900000,0:3]
#print(np.shape(x_test))
#print(x_test)
y_test=data[800000:900000,6]
#print(np.shape(y_test))
#print(y_test)
y_test=y_test-1
y_test/=10

y_train=np.trunc(y_train)
y_test=np.trunc(y_test)
#y_train=np.arange(y_train)
#y_test=y_test.flatten()
print(y_train)
print(np.ndim(y_train))
print(np.shape(y_train))



y_train=np_utils.to_categorical(y_train,10)
print(y_train)
y_test=np_utils.to_categorical(y_test,10)


model = Sequential()
model.add(Dense(500,input_dim=3))
model.add(Activation('relu'))



model.add(Dense(300))
model.add(Activation('relu'))

model.add(Dense(100))
model.add(Activation('relu'))


model.add(Dense(10))
model.add(Activation('softmax'))




model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.01),metrics=['accuracy'])


epochs=10
batch_size=50

model.fit(x_train,y_train,epochs=epochs,batch_size=batch_size,validation_data=(x_test,y_test))


loss_and_metrics=model.evaluate(x_test,y_test)
print(loss_and_metrics)
