import numpy as np #numpyのライブラリを定義
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD

np.random.seed(0) #乱数のシード

model=Sequential() #層構造の定義
model.add(Dense(input_dim=2,units=1))
model.add(Activation('sigmoid')) #活性化関数をシグモイド

model.compile(loss='binary_crossentropy',optimizer=SGD(lr=0.1)) #確率的勾配降下法,lrは学習率


#ORゲート
X=np.array([[0,0],[0,1],[1,0],[1,1]])
Y=np.array([[0],[1],[1],[1]])

model.fit(X,Y,epochs=200,batch_size=1)#訓練を行う

#学習結果の確認
classes=model.predict_classes(X,batch_size=1)
prob =model.predict_proba(X,batch_size=1)

print('classified:')
print(Y == classes)#答えと目的変数が一緒だった場合true
print()
print('output probability:')
print(prob)#確率がゼロに近いということは0ということ
