# Vapour
NodeEditor basiced on Qt and OpenGL/CV  

基于Qt编写的节点编辑器  
将会用于网格建模/几何处理、shader材质编辑、图像处理  

2021-5-17: 完成背景绘制，右键菜单，节点连线，节点删除，初步拓扑排序  
(细节)连线位于节点层级之下，使用lambda处理右键菜单slot，节点创建生成在鼠标位置处  




待解决：  
序列化与反序列化——json  
可拓展的数据与节点UI  
历史记录栈  
copy和paste  
shift加选  
删除节点会崩溃的问题，应该是node间关系的问题:注释掉deleteItem的delete解决。这里的delete必须存在吗？似乎不delete就没有释放内存，寻求更好的方法  

分类数据输入与输出和传递的问题  
addNode 中的Node new是否正常释放了？需要手动delete吗？  
qss 加载不影响的问题  
右键菜单中菜单(引出多选项)  
增加连线模式以无需任何release都计算是否连线  
edge和edgetemp有时不一样   
删除节点时同时删除相关连线  
优化deleteItem算法  
检查删除和增加节点与连线时socket，node变量例如isconnect的改变  
节点QList的清空以及内存检查  
QGraphicsScene::removeItem: item 0x2c94ee0's scene (0x0) is different from this scene (0x2bdd7d0)  

单片机类型的编写  
