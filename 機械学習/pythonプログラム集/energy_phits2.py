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
print(np.shape(x_train))
#print(x_train)
y_train=data[0:800000,6]#入射エネルギー情報をとってくる
print(y_train)
y_train=y_train-1

print(y_train)
#y_train/=100


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
#y_test/=100

y_train=np.trunc(y_train)
y_test=np.trunc(y_test)
#y_train=np.arange(y_train)
#y_test=y_test.flatten()
print(y_train)
print(np.ndim(y_train))
print(np.shape(y_train))



y_train=np_utils.to_categorical(y_train,100)#ワンホット化
print(np.shape(y_train))
y_test=np_utils.to_categorical(y_test,100)#ワンホット化


model = Sequential()
model.add(Dense(500,input_dim=3))
model.add(Activation('relu'))



#model.add(Dense(300))
#model.add(Activation('relu'))

model.add(Dense(300))
model.add(Activation('relu'))


model.add(Dense(100))
model.add(Activation('softmax'))




model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.01),metrics=['accuracy'])


epochs=5
batch_size=50

model.fit(x_train,y_train,epochs=epochs,batch_size=batch_size,validation_data=(x_test,y_test))


loss_and_metrics=model.evaluate(x_test,y_test)
print(loss_and_metrics)



model.evaluate(x_test,y_test,verbose=0)
predict=model.predict(x_test)
path_w1 ='/mnt/c/Users/komori/Desktop/test1.csv'
path_w2 ='/mnt/c/Users/komori/Desktop/test2.csv'

y_test=np.savetxt(path_w1,y_test,delimiter=",",fmt="%s")
predict=np.savetxt(path_w2,predict,delimiter=",",fmt="%s")
# print(y_test)




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
