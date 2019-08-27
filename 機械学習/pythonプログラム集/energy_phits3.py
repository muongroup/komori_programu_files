import keras
import numpy as np
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD
from keras.optimizers import Adam
from keras.optimizers import Nadam
from keras.utils import np_utils
import pandas as pd
import csv #csvファイルの読みこみ

#/home/komori/python_practice/machine_learning_data_set/
data1 = pd.read_csv('output1.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
#data2 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data1_5_2.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
#data3 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data1_5_3.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 

#print(type(data))
data=data.sample(frac=1)#データのシャッフル
data=data.values#pandasをnumpyに変更
#data2=data2.sample(frac=1)#データのシャッフル
#data2=data2.values#pandasをnumpyに変更
#data3=data3.sample(frac=1)#データのシャッフル
#data3=data3.values#pandasをnumpyに変更

#data=np.r_[data1,data2,data3]
#print(type(data))
print(np.shape(data))
#print(data[4])

#学習用のデータ
x_train=data[0:2000000,0:10]#配列の0列目からシンチの付与エネルギー情報が入っている
print(x_train)
#x_train=x_train**2#二乗
#x_train=np.log10(x_train)#log10
print(x_train)
x_train=x_train.round(1)
#print(np.shape(x_train))
#print(x_train)
y_train=data[0:2000000,19]#入射エネルギー情報をとってくる
print(y_train)
y_train=np.ceil(y_train)
y_train=y_train-1
print(y_train)
y_train/=1

#print(np.shape(y_train))
#print(np.round(y_train))
print(y_train)

#テスト用のデータ
x_test=data[200000:2500000,0:4]
#x_test=x_test**2 #データの前処理二乗
#x_test=np.log10(x_test)#データの前処理ログ
#print(np.shape(x_test))
#print(x_test)
x_test=x_test.round(1)
y_test=data[200000:2500000,19]

#print(np.shape(y_test))
#print(y_test)
y_test=np.ceil(y_test)
y_test=y_test-1
y_test/=1

y_train=np.trunc(y_train)
y_test=np.trunc(y_test)
#y_train=np.arange(y_train)
#y_test=y_test.flatten()
print(y_train)
print(np.ndim(y_train))
print(np.shape(y_train))



y_train=np_utils.to_categorical(y_train,300)#ワンホット化
print(np.shape(y_train))
y_test=np_utils.to_categorical(y_test,300)#ワンホット化


model = Sequential()
model.add(Dense(1000,input_dim=10))
model.add(Activation('relu'))


#model.add(Dense(1000))
#model.add(Activation('relu'))


model.add(Dense(500))
model.add(Activation('relu'))

#model.add(Dense(10))
#model.add(Activation('relu'))

#model.add(Dense(100))
#model.add(Activation('relu'))


model.add(Dense(300))
model.add(Activation('softmax'))




model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.01,momentum=0.0,decay=0.0,nesterov=False),metrics=['accuracy'])

#model.compile(loss='categorical_crossentropy',optimizer=Adam(lr=0.001,beta_1=0.9,beta_2=0.999,epsilon=None,decay=0.0,amsgrad=False),metrics=['accuracy'])
#model.compile(loss='categorical_crossentropy',optimizer=Nadam(lr=0.002,beta_1=0.9,beta_2=0.999,epsilon=None,schedule_decay=0.004),metrics=['accuracy'])


epochs=20
batch_size=20

result=model.fit(x_train,y_train,epochs=epochs,batch_size=batch_size,validation_data=(x_test,y_test))


loss_and_metrics=model.evaluate(x_test,y_test)
print(loss_and_metrics)



score=model.evaluate(x_test,y_test,verbose=0)

print(result.history)
acc=result.history['acc']#学習用データの精度
loss=result.history['loss']#学習用データの損失関数
val_acc=result.history['val_acc']#検証用データの精度
val_loss=result.history['val_loss']#検証用データの損失関数


print(acc)#
print(np.c_[acc,loss,val_acc,val_loss])#配列の結合

path_w3 ='test3.csv'
path_w4 ='correct_output.txt'
path_w5 ='correct_output.csv'
history=np.savetxt(path_w3,np.c_[acc,loss,val_acc,val_loss],delimiter=",",fmt="%s",header='acc,loss,val_acc,val_loss')

predict=model.predict(x_test)
#path_w1 ='/mnt/c/Users/komori/Desktop/test1.csv'
#path_w2 ='/mnt/c/Users/komori/Desktop/test2.csv'

#y_test=np.savetxt(path_w1,y_test,delimiter=",",fmt="%s")
#predict=np.savetxt(path_w2,predict,delimiter=",",fmt="%s")
# print(y_test)
predict_max=predict.argmax(axis=1)
print(y_test.argmax(axis=1))
connect=np.c_[y_test_max,predict_max]
correct_output=np.savetxt(path_w4,connect,delimiter=" ",fmt="%s")



#検証用のデータをあとから使うために保存する
test_data=np.c_[x_test,y_test]
history=np.savetxt(path_w5,test_data,delimiter=",",fmt="%s",header='pla1,pla2,pla3,iron1,iron2,incident')

#重みを保存する
json_string=model.to_json()
yaml_string=model.to_yaml()
model.save_weights('/mnt/c/Users/komori/Desktop/weihgts.h5');
open('/mnt/c/Users/komori/Desktop/model.json','w').write(json_string)


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
