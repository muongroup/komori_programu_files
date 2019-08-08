import keras
import numpy as np
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD
from keras.utils import np_utils
import pandas as pd
from keras.models import model_from_json
import csv #csvファイルの読みこみ

#home/komori/python_practice/machine_learning_data_set/
data1 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data_1_4_1.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
data2 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data_1_4_2.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
data3 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data_1_4_3.csv',sep=',')#csvファイルを読み込んだ番上の行をラベルと認識してくれる 



min=0
max=min+300

data1=data1[data1['入射エネルギー']>min]
data1=data1[data1['入射エネルギー']<=max]#データの抽出
data2=data2[data2['入射エネルギー']>min]
data2=data2[data2['入射エネルギー']<=max]#データの抽出
data3=data3[data3['入射エネルギー']>min]
data3=data3[data3['入射エネルギー']<=max]#データの抽出

data1 =data1.sample(frac=1)#ランダムにかき混ぜ
data1=data1.values#pandasをnumpyに変更
data2 =data2.sample(frac=1)#ランダムにかき混ぜ
data2=data2.values#pandasをnumpyに変更
data3 =data3.sample(frac=1)#ランダムにかき混ぜ
data3=data3.values#pandasをnumpyに変更

data=np.r_[data1,data2,data3]

#print(type(data))
print(np.shape(data))
#print(data[4])

#学習用のデータ
#x_train=data[0:800000,0:3]#配列の0列目からシンチの付与エネルギー情報が入っている
#print(np.shape(x_train))
#print(x_train)
#y_train=data[0:800000,6]#入射エネルギー情報をとってくる
#print(y_train)
#y_train=y_train-1

#print(y_train)
#y_train/=100


#print(np.shape(y_train))
#print(np.round(y_train))
#print(y_train)

#テスト用のデータ
x_test=data[0:2500000,0:3]
#print(np.shape(x_test))
print(x_test)
x_test=x_test.round(1)
print(x_test)
y_test=data[0:2500000,5]
#print(np.shape(y_test))
print(y_test)
y_test=np.ceil(y_test)
y_test=y_test-1
y_test/=10

#y_train=np.trunc(y_train)
y_test=np.trunc(y_test)
#y_train=np.arange(y_train)
#y_test=y_test.flatten()
#print(y_train)
#print(np.ndim(y_train))
#print(np.shape(y_train))



#y_train=np_utils.to_categorical(y_train,100)#ワンホット化
#print(np.shape(y_train))
y_test=np_utils.to_categorical(y_test,30)#ワンホット化

#モデルの読み込み
model = model_from_json(open('/mnt/c/Users/komori/Desktop/weight_30/model.json','r').read())
model.load_weights('/mnt/c/Users/komori/Desktop/weight_30/weihgts.h5')





model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.01),metrics=['accuracy'])


#epochs=1
#batch_size=50



loss_and_metrics=model.evaluate(x_test,y_test)
print(loss_and_metrics)



model.evaluate(x_test,y_test,verbose=0)
predict=model.predict(x_test)
path_w1 ='/mnt/c/Users/komori/Desktop/test1.csv'
path_w2 ='/mnt/c/Users/komori/Desktop/test2.csv'
path_w3 ='/mnt/c/Users/komori/Desktop/1MeV刻みごとのデータ/accuracydata.txt'
y_test_sum=np.sum(y_test,axis=0)#各ビン毎に足し合わせる
#y_testt=y_testt.reshape(1,30)#各ビンごとに足し合わせる
predict_sum=np.sum(predict,axis=0)#各ビンごとに足し合わせる
#predictt=predictt.reshape(1,30)#各ビンごとに足し合わせる

#y_test=np.r_[y_test,y_testt]#
#predict=np.r_[predict,predictt]
#y_test=np.savetxt(path_w1,y_test,delimiter=",",fmt="%s")
#predict=np.savetxt(path_w2,predict,delimiter=",",fmt="%s")
#np.savetxt(path_w3,np.c_[y_test_sum,predict_sum],delimiter=" ",fmt="%s")
# print(y_test)

#json_string=model.to_json()
#yaml_string=model.to_yaml()
#model.save_weights('/mnt/c/Users/komori/Desktop/weihgts.h5');
#open('/mnt/c/Users/komori/Desktop/model.json','w').write(json_string)


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
