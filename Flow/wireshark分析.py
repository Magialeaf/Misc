import pyshark
import base64


if __name__ == '__main__':
    count = []
    # 加载本地的pcap文件
    capture = pyshark.FileCapture('fetus_pcap.pcap',tshark_path='D:\CTF\Capoo\Internet\Wireshark\\')
    for packet in capture:
        for pack in packet:
            if pack.layer_name == 'icmp':
                if int(pack.type) != 0:
                    count.append(int(pack.data_len))  # 加上 int 转类型，否则是类接下来无法迭代
    res = ""
    for i in count:
        res += chr(i)
    print(res)
    print(base64.b64decode(res))
