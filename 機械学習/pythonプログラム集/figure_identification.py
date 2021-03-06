import keras
import numpy as np
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD
from keras.utils import np_utils

import matplotlib.pyplot as plt#グラフを作るときに必要な奴
#from sklearn import datasets


#indices = np.random.permutation(range(n))[:N]#要素数7万を並び替えそこからNこのデータをとってくる

(x_train,y_train),(x_test,y_test)=mnist.load_data()
#ここまではすべてがテンソルの状態(ndarrayの形)


'''
print(np.shape(x_train))
print(np.shape(y_train))
print(np.shape(x_test))
print(np.shape(y_test))
'''

#配列の形を変える
x_train=x_train.reshape(60000,784)
x_test=x_test.reshape(10000,784)

#print(type(x_train))
x_train=x_train[0:10000,:] #ここで学習データの取り出す部分を決めてあげる
#print(type(x_train))
y_train=y_train[0:10000]#ここで学習データの取り出す部分を決めてあげる
y_train=int(y_train)
print(y_train)
print(np.ndim(y_train))
print(type(y_train))
y_train=keras.utils.to_categorical(y_train,10)
y_test=keras.utils.to_categorical(y_test,10)
print(np.shape(y_train))




model=Sequential()
model.add(Dense(200,input_dim=784))#入力層784、隠れ層200
model.add(Activation('sigmoid'))


model.add(Dense(200))#隠れ層200
model.add(Activation('relu'))

model.add(Dense(200))#隠れ層200
model.add(Activation('relu'))



model.add(Dense(10))
model.add(Activation('softmax'))

model.compile(loss='categorical_crossentropy',optimizer=SGD(lr=0.01),metrics=['accuracy'])

epochs=500
batch_size=100

hist=model.fit(x_train,y_train,epochs=epochs,batch_size=batch_size,validation_data=( x_test, y_test))

loss_and_metrics = model.evaluate(x_test,y_test)
print(loss_and_metrics)

val_loss = hist.history['val_loss']
val_acc = hist.history['val_acc']

plt.rc('font',family = 'selfif')
fig = plt.figure()
plt.plot(range(epochs),val_acc,label='value_acc',color = 'black')
plt.plot(range(epochs),val_loss,label='value_loss',color = 'black')
plt.xlabel('epochs')
plt.show()







