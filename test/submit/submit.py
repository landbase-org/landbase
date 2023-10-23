# -*- coding: UTF-8 -*-
"""
@Date    :2023/9/29 10:24
@Author  :hl
@File    :te.py
"""
import sys
from threading import Thread
import time
from datetime import datetime
import requests
import yaml
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5 as PKCS1_cipher
import base64
from argparse import ArgumentParser
from colorama import init as colorama_init, Fore

# colorama_init()  # 保证输出的字符为ANSA字符
PUBLIC_KEY = '-----BEGIN PUBLIC KEY-----\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAs9aN3CjNoHwPVaSUamb001aG4tneAjvMajLiyNUQmVgz/qkvt0gwVpi/iogGZllXpvY6VUb3GxHXCjghwh1ZgfSLBrvdqj3Pkk1h8arduWqqlvLU0kRRoqNrrKvmVzFUUqFx/yrgVp4PQbPvDhXWeeFWPBt8uwcZ186hV2WCQ9s5G4JQ81E3lHWLXPAZhmq3pHl7c26hLAwReXKq9lcAsubLHCVLntnnxjTQkyU8U19P5dCmTrv/OonoW87skNiBEPgb3hE7B7+9DmYlYzYSz8QEO7wtPthIyZsZZPNbDGQwpRkCXWO6vIE7OgU4Kou4XWZk4uNgLGuAWkfuJst9VwIDAQAB\n-----END PUBLIC KEY-----'


def rsa_encrypt(message):
    key = PUBLIC_KEY
    pub_key = RSA.importKey(str(key))
    cipher = PKCS1_cipher.new(pub_key)
    return base64.b64encode(cipher.encrypt(bytes(message.encode("utf8")))).decode('utf-8')


def init_args():
    options_parser = ArgumentParser()
    config = None
    with open('./config.yaml', 'r', encoding='utf-8') as f:
        config = dict(yaml.load(f, yaml.FullLoader))

    options_parser.add_argument("--mode", type=str, help="模式", default=config.get('mode'))

    options_parser.add_argument("--year", type=str, help="提交的年份(2022 or 2023)", default=config.get('year'))
    options_parser.add_argument("--git_repo", type=str, help="当前提交的仓库地址", default=config.get('git_repo'))
    options_parser.add_argument("--branch", type=str, help="提交的分支", default=config.get('branch'))
    options_parser.add_argument("--commit_id", type=str, help="提交的ID", default='')

    options_parser.add_argument("--list", type=str,
                                help="允许显示, 提交结果中的错误信息, 如果不提供, 则不显示错误信息", default=config.get('list'))
    options_parser.add_argument("--lis_num", type=int, help="显示提交列表中的第几个, 默认最近提交的", default=config.get('lis_num'))
    options_parser.add_argument("--write_file", type=str, help="是否将结果写入到文件中", default=config.get('write_file'))

    options_parser.add_argument("--user", type=str, help="用户名", default=config.get('user'))
    options_parser.add_argument("--pwd", type=str, help="密码", default=config.get('pwd'))

    # (3) 读取命令行参数, 初始化到options中
    options = options_parser.parse_args()
    print(options)

    # 预处理参数, 转化为列表
    if options.list == '':  # 如果没有参数则为空列表
        options.list = []
    else:
        options.list = options.list.split(',')

    # 预处理提交的年份
    if options.year == '2022':
        options.year = '500003'
    else:
        options.year = '600004'

    return options


# 返回现在的时间和开始的时间之间的差值, 并转化为时分秒的格式
def timer(begin_time, status: list, desc="执行中"):
    while status[0] == 1:
        now_time = time.time()
        time_difference = now_time - begin_time
        m, s = divmod(time_difference, 60)
        h, m = divmod(m, 60)
        print('\r' + Fore.GREEN + f'{desc}, 耗时: {int(h):02d}:{int(m):02d}:{int(s):02d}' + Fore.RESET, end='',
              flush=True)
        time.sleep(1)


class Ocean(object):
    def __init__(self):
        self.args = init_args()  # 需要第一时间初始化args

        self.session = self.get_session()
        self.mode = self.args.mode
        self.lis_num = self.args.lis_num  # 查询所有提交中的第几个任务
        self.questions = None
        self.passed_questions = None
        self.failure_questions = None
        self.task_status = [0]  # 任务状态1表示正在执行 2表示执行完成, 3表示执行失败, 0表示还没初始化用列表传递地址, 能够修改
        self.task_waiting = [0]  # 表示当前任务正在等待执行 0 表示等待初始化, 1表示正在执行, 2表示执行完成
        self.timer_task = None  # 记时线程
        self.timer_task_waiting = None

    def __del__(self):
        try:
            if self.timer_task is not None:
                self.timer_task.join()
            if self.timer_task_waiting is not None:
                self.timer_task_waiting.join()
        except Exception as e:
            pass

        print(Fore.CYAN + "脚本运行完毕" + Fore.RESET)

    def get_session(self):
        headers = {
            'authority': 'obiamweb.oceanbase.com',
            'accept': 'application/json',
            'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8',
            'authorization': '',
            'cache-control': 'no-cache',
            'content-type': 'application/json',
            # 'cookie': 'Hm_lvt_c6b821bb340e61f0d507b9bef3bd4d5b=1695958102; Hm_lpvt_c6b821bb340e61f0d507b9bef3bd4d5b=1695958102; _ga=GA1.1.433611206.1695958102; spanner=itNtHQ215DVEXtClWMqo33VC8Lx3EbP4Xt2T4qEYgj0=; _ga_T35KTM57DZ=GS1.1.1695958102.1.0.1695958107.55.0.0; RDS-APP-ID=obiamweb_pwdLogin; RDS-TOKEN=8dd6af6722534ce8807751672e88e5d369d14da15a924359a9d697f3e3122f58; RDS-BIZ-NO=xc3GfHa627QDWnJYZxYSkdCES47PcZ_je_CH2ewsDHTxmwSYc7JeC46rkPbp4i6Y',
            'origin': 'https://open.oceanbase.com',
            'pragma': 'no-cache',
            'referer': 'https://open.oceanbase.com/',
            'sec-ch-ua': '"Google Chrome";v="117", "Not;A=Brand";v="8", "Chromium";v="117"',
            'sec-ch-ua-mobile': '?0',
            'sec-ch-ua-platform': '"Windows"',
            'sec-fetch-dest': 'empty',
            'sec-fetch-mode': 'cors',
            'sec-fetch-site': 'same-site',
            'security-code': '',
            'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36',
            'x-aciamweb-tenant': '',
            'x-aciamweb-tenant-id': '',
            'x-from-aciamweb': 'true',
        }

        json_data = {
            'passAccountName': str(self.args.user),
            'password': rsa_encrypt(str(self.args.pwd)),
            'registerFrom': 1,
        }
        session = requests.session()
        session.headers = headers
        session.post(
            'https://obiamweb.oceanbase.com/webapi/aciamweb/login/publicLogin',
            json=json_data,
        )
        return session

    def get_questions_detail(self):
        """获取问题的内容"""
        params = {
            'rpcFromType': '0',
            'questionId': self.args.year,
            'pageNo': '1',
            'pageSize': '25',
            'subQuestionName': '',
            'sortType': '1',
        }
        response = self.session.get(
            'https://openwebapi.oceanbase.com/api/techcamp/testplatform/subquestion/queryTestPlatformSubQuestionList',
            params=params,
        )
        lis = response.json()['data']['list']
        ret = []
        for li in lis:
            dic = {
                'title': li['subQuestionName'],
                'passNumber': li['passNumber'],
                'noPassNumber': li['noPassNumber'],
                'score': li['subQuestionTotalScore'],
                'level': li['difficulty'],
                'detail': li['subQuestionDetail'],  # 具体内容
                'passRate': li['passRate'],
            }
            ret.append(dic)

        self.questions = sorted(ret, key=lambda x: float(x['passRate']), reverse=True)

    def get_submit_detail(self):
        cur_time = time.time()
        params = {
            'questionId': self.args.year,
        }

        response = self.session.get(
            'https://openwebapi.oceanbase.com/api/techcamp/testplatform/taskrecord/queryTestPlatformTaskRecordList',
            params=params,
        )
        cur_task = response.json()['data']['list'][self.lis_num]
        if cur_task['taskStatus'] == 1:  # 当前任务正在执行
            if self.task_status[0] == 0:  # 计时器还没初始化

                # 等待之后加入到执行
                self.task_waiting[0] = 2  # 等待队列执行完成
                try:
                    self.timer_task_waiting.join()  # 等待当前任务执行完毕
                    print()

                except AttributeError as e:
                    pass

                self.task_status[0] = 1
                self.timer_task = Thread(target=timer, args=(time.time(), self.task_status))
                self.timer_task.start()

            time.sleep(10)  # 没十秒查询一次结果
            return self.get_submit_detail()  # 回调函数
        elif cur_task['taskStatus'] == 3:  # 任务执行失败
            self.task_status[0] = 3  # 任务执行失败
        else:
            if list(response.json()['data']['list'])[self.lis_num]['testCaseResult'] is None:  # 正在提交中
                if self.task_waiting[0] == 0:  # 等待计时器还没初始化
                    self.task_waiting[0] = 1
                    self.timer_task_waiting = Thread(target=timer, args=(time.time(), self.task_waiting, "等待执行"))
                    self.timer_task_waiting.start()
                return self.get_submit_detail()  # 回调函数

            self.task_status[0] = 2  # 任务执行完成
            try:
                self.timer_task.join()
                print()
            except AttributeError as e:
                pass

            try:
                lis = eval(list(response.json()['data']['list'])[self.lis_num]['testCaseResult'])

                passed = []  # title
                failure = []  # title, message(失败的原因)
                for li in lis:
                    if li['resultStatus'] == 1:  # 通过该题
                        passed.append({
                            'title': li['testCase'],
                        })
                    else:
                        failure.append({
                            'title': li['testCase'],
                            'message': li['message'],
                        })

                self.passed_questions = passed
                self.failure_questions = failure
            except Exception as e:
                print(response.json())

    # 拼接问题和提交返回的内容
    def contact_questions_and_submit(self):
        # 将是否通过拼接到questions中
        for question in self.questions:
            question['passed'] = "❌"
            for p in self.passed_questions:
                if p['title'] == question['title']:
                    question['passed'] = "✅"
                    break

            for f in self.failure_questions:
                if f['title'] == question['title'] and f.get('message') is not None:  # 如果当前错误信息在允许显示的列表中, 加入到答案中去
                    question['message'] = f['message']

    def submit(self):
        """提交内容"""
        json_data = {
            'questionId': self.args.year,
            'gitRepo': self.args.git_repo,
            'commitId': self.args.commit_id,
            'branch': self.args.branch,
        }

        response = self.session.post(
            'https://openwebapi.oceanbase.com/api/techcamp/testplatform/taskrecord/commitTestPlatformTaskRecord',
            json=json_data,
        )

        # 打印提交的结果
        try:
            response.json()['message']
            print(Fore.GREEN + response.json()['message'] + Fore.RESET)
        except Exception as e:
            print(response.json())

    # 将题目列表写入到文件夹中
    def update_question_list(self):
        """执行该函数之前需要调用`get_submit_detail` 获取提交通过情况"""
        with open('question_list.md', 'w', encoding='utf-8') as f:
            # 写入时间
            f.write(f"{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
            for question in self.questions:
                f.write(f"# {question['passed']} {question['passRate']}% `{question['title']}`\n")

    def print_msg_list(self):
        """显示错误信息列表在terminal"""
        for question in self.questions:
            if question['title'] in self.args.list:
                msg = question.get('message')
                if msg is None:  # 当前任务通过了
                    print(Fore.GREEN + f"✅ {question['title']}" + Fore.RESET)
                else:
                    print(Fore.RED + f"❌ {question['title']}\n{question['message']}" + Fore.RESET)

        # 将所有答案写入到文件中
        with open('./question_list_ret.md', 'w', encoding='utf-8') as f:
            passed = []
            failid = []
            for idx, question in enumerate(self.questions):
                msg = question.get('message')
                if msg is None:  # 当前任务通过了
                    passed.append(f"✅ {question['title']}\n\n")
                else:
                    failid.append(f"# ❌ {question['title']}\n"
                            f"```sql\n"
                            f"{question['message']}\n"
                            f"```\n")
            # 写入到文件中
            f.write('# PASSED\n')
            [f.write(p) for p in passed]
            [f.write(x) for x in failid]


    def update_question_list_detail(self):
        with open('question_list_detail.md', 'w', encoding='utf-8') as f:
            # 写入时间
            f.write(f"{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
            for question in self.questions:
                f.write(f"# {question['passed']} {question['passRate']}% `{question['title']}`\n")
                f.write(f"**分数**: {question['score']}\n\n")
                f.write(f"**难度**: {question['level']}\n\n")
                f.write(
                    f"**通过次数**: {question['passNumber']}/{str(int(question['passNumber']) + int(question['noPassNumber']))}\n\n")
                f.write(f"{question['detail']}\n\n")

    def run(self):
        self.get_questions_detail()  # 获取问题的详细

        if self.mode == 'query':  # 查询问题
            self.get_submit_detail()  # 获取任务详细

            # 拼接问题和是否通过
            self.contact_questions_and_submit()

            # 在控制台输出选择列表是否通过和错误信息
            self.print_msg_list()

        elif self.mode == 'submit':  # 提交任务
            self.submit()  # 提交任务
            self.get_submit_detail()  # 获取任务详细

            # 拼接问题和是否通过
            self.contact_questions_and_submit()

            # 在控制台输出选择列表是否通过和错误信息
            self.print_msg_list()

        if self.args.write_file == 'true':
            # 将结果写入到文件中
            self.update_question_list()
            self.update_question_list_detail()


if __name__ == '__main__':
    ocean = Ocean()
    ocean.run()
