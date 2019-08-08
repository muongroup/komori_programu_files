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


with open('/mnt/c/Users/komori/Desktop/1MeV刻みごとのデータ/eachaccuracy.txt','a') as f:#ループごとの損失値と正答率の書き出すファイルまでのパス




 for i in range(30):#検証用データをエネルギーごとに分けて読み込ませるためここで繰り返す
  #検証用データを読み込む (三つのファイルに分けているのはExcelが100万以上のけたを読み切れないため)
  data1 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data1_6_1.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
  data2 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data1_6_2.csv',sep=',')#csvファイルを読み込んだ一番上の行をラベルと認識してくれる 
  data3 = pd.read_csv('/mnt/c/Users/komori/Desktop/machine_learning_data_set/data1_6_3.csv',sep=',')#csvファイルを読み込んだ番上の行をラベルと認識してくれる 

#for i in range(30):
#読み込ませたいデータの上限値と下限値をここで決める
  min=i*10
  max=min+10

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
  
  data=np.r_[data1,data2,data3]#三つのデータファイルを統合

#print(type(data))
#  print(np.shape(data))
#print(data[4])


#テスト用のデータ
  x_test=data[0:50000,0:4]
#print(np.shape(x_test))
  print(x_test)
  x_test=x_test.round(1)#小数1桁を四捨五入
  print(x_test)
  y_test=data[0:50000,19]
#print(np.shape(y_test))
  print(y_test)
  y_test=np.ceil(y_test)#ceilは切り上げ
  y_test=y_test-1#
  y_test/=1

  y_test=np.trunc(y_test)
 # print(np.ndim(y_test))
 # print(np.shape(y_test))

  y_test=np_utils.to_categorical(y_test,300)#ワンホット化

#モデルの読み込み#ほかのプログラムで作ったモデルの値を読みこむ
  model = model_from_json(open('/mnt/c/Users/komori/Desktop/19層シミュレーション/プラシン4/model.json','r').read())
  model.load_weights('/mnt/c/Users/komori/Desktop/19層シミュレーション/プラシン4/weihgts.h5')





  model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.01,momentum=0.0,decay=0.0,nesterov=False),metrics=['accuracy'])


#epochs=1
#batch_size=50


 #loss_and_metricsに
  loss_and_metrics=model.evaluate(x_test,y_test,verbose=0)
  print(loss_and_metrics)
  print(np.shape(loss_and_metrics))
#  loss_and_metrics=loss_and_metrics.T


 # model.evaluate(x_test,y_test,verbose=0)
  predict=model.predict(x_test)
  path_w1 ='/mnt/c/Users/komori/Desktop/test1.csv'
  path_w2 ='/mnt/c/Users/komori/Desktop/test2.csv'
  
  path_w3 ='/mnt/c/Users/komori/Desktop/1MeV刻みごとのデータ/accuracy'+str(i)+'.txt'

  y_test_sum=np.sum(y_test,axis=0)#各ビン毎に正解値を足し合わせる
  predict_sum=np.sum(predict,axis=0)#各ビンごとに出力値を足し合わせる



  
#  y_test=np.savetxt(path_w1,y_test,delimiter=",",fmt="%s")
#  predict=np.savetxt(path_w2,predict,delimiter=",",fmt="%s")
  np.savetxt(path_w3,np.c_[y_test_sum,predict_sum],delimiter=" ",fmt="%s")#path_w3の場所に正解値と出力値を出力する
# with open('/mnt/c/Users/komori/Desktop/1MeV刻みごとのデータ/eachaccuracy.txt','a') as f:
#  np.savetxt(f,loss_and_metrics,delimiter=" ",fmt="%s")
  f.write(str(loss_and_metrics[0])+' '+str(loss_and_metrics[1])+'\n')#各ループごとに損失関数の値と正答率を保存
  
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
