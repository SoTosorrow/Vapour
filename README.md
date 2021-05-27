# Vapour
基于Qt的轻量级的节点式几何建模工具与shader材质生成工具  
正在加入图像处理(合成)的功能  
几何建模与shader生成待开发  

日志:  
* 2021-5-21: 重构框架基本完成，交互由action扩展、形状由descriptor扩展，数据处理由node扩展  
* 2021-5-22: 构建图像处理节点的基础  
* 2021-5-23: 完成node的解耦，添加了Double节点  
还需要解耦Descriptor  
(细节)连线位于节点层级之下，使用lambda处理右键菜单slot，节点创建生成在鼠标位置处,右键菜单,拓扑排序  
* 考虑用模板多态？虚函数多态性能较差，会阻止编译器优化



待解决:  
改进多线程，节点线程操作系统式调度，加锁和多次shift S安全检测  
解耦Descriptor  
序列化与反序列化——json  
更便捷的注册新节点，比如在右键菜单加入和在addnode加入,根据json文档扩建新节点  
历史记录栈  
copy和paste  
setHeight 遮住的问题两个Height的问题，是子节点的height被父节点的height遮住了吗？清减这一块问题  

内存还是有一点泄漏，需要检查修复，以及内存释放的问题，包括QListQPair  
基类析构函数设计为virtual  
右键菜单的QAction会造成内存泄漏   
删除节点时同时删除相关连线,优化或重写deleteItem算法并处理内存释放  

数值的传递，现在是值传递，改成指针  
加入节点!canCompute时  
不同socket区分，处理区分  

分类数据输入与输出和传递的问题  
addNode 中的Node new是否正常释放了？需要手动delete吗？  
增加连线模式以无需任何release都计算是否连线  
检查删除和增加节点与连线时socket，node变量例如isconnect的改变  
单片机类型的编写开发，与或非二进制数据处理  
