# Vapour
基于Qt的轻量级的节点式几何建模工具与shader材质生成工具  
可能加入图像处理(合成)的功能  

日志:  
* 2021-5-17: 完成背景绘制，右键菜单，节点连线，节点删除，初步拓扑排序  
(细节)连线位于节点层级之下，使用lambda处理右键菜单slot，节点创建生成在鼠标位置处  
* 2021-5-18: 完成节点UI的扩展，number节点处理  



待解决：  
序列化与反序列化——json  
根据json文档扩建新节点  
可拓展的数据与节点UI  
历史记录栈  
copy和paste  
shift加选  
删除节点会崩溃的问题，应该是node间关系的问题:注释掉deleteItem的delete解决。这里的delete必须存在吗？似乎不delete就没有释放内存，寻求更好的方法  
内存还是有一点泄漏，需要检查修复，以及内存释放的问题  
数值的传递，现在是值传递，改成指针  
initData的设计  
重新设计数据传输储存和处理部分  
加入节点!canCompute时  
不同socket区分，处理区分  

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
开发与或非二进制数据处理  
右键菜单的QAction会造成内存泄漏  
terminate called without an active exception  
