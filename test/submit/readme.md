[TOC]

# 依赖
使用`conda`导入环境文件`conda_env.yaml`

```shell
conda env create -f conda_env.yaml
```

# 快速开始

```shell
python3 submit.py
```





`python3 submit.py --mode=mode --list='' --write_file=true`

--mode: 有`query`和`submit`两个选项, **默认**为`query`

--list: 为要在控制台显示结果的查询, 如果通过则显示通过, 如果没有通过则打印错误信息, list中名字如果包括`-`字符, 需要用引号引上

--write_file: 是否将结果写入到文件中, 默认为`true`

--branch: 提交的分支, 默认为'master'

--year: 提交的年份， 默认为2022年

# 查询结果模式(`--mode=query`)

## 选择某几个功能查询, 输出到控制台(`--list`)

`python3 submit.py --mode=query --list='date,basic,aggregation-func' --write_file=false`

![image-20230929233242447](https://my-img-typora.oss-cn-chengdu.aliyuncs.com/img/image-20230929233242447.png)

## 输出到文件(`--write_file`)

`python3 submit.py`

默认是`query`模式

输出的文件有两个

`question_list_md` 题目的缩略图

![image-20230929233522422](https://my-img-typora.oss-cn-chengdu.aliyuncs.com/img/image-20230929233522422.png)

`question_list_detail.md` 题目的详细信息

![image-20230929233613599](https://my-img-typora.oss-cn-chengdu.aliyuncs.com/img/image-20230929233613599.png)

# 提交模式(`--mode=submit`)

`python3 submit.py --mode=submit --branch=aggregation --list='aggregation-func'`

![image-20230930001901713](https://my-img-typora.oss-cn-chengdu.aliyuncs.com/img/image-20230930001901713.png)

`python3 submit.py --mode=submit --branch=aggregation --list='aggregation-func,alias'`

![image-20230930004629263](https://my-img-typora.oss-cn-chengdu.aliyuncs.com/img/image-20230930004629263.png)

会显示执行时间, 和错误样例, 已知BUG, 可能会在记时的时候`ctrl c`退出不了, 直接关闭终端就行了

