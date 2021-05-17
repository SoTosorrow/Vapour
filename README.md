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

分类数据输入与输出和传递的问题  
addNode 中的Node new是否正常释放了？需要手动delete吗？  
qss 加载不影响的问题  
右键菜单中菜单(引出多选项)  
增加连线模式以无需任何release都计算是否连线  
edge和edgetemp有时不一样  
Node应该包含socket来判断还是包含edge来判断呢  
删除节点时同时删除相关连线  
优化deleteItem算法  
QGraphicsScene::removeItem: item 0x2c94ee0's scene (0x0) is different from this scene (0x2bdd7d0)  
检查删除和增加节点与连线时socket，node变量例如isconnect的改变  
