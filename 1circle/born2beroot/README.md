# Born2beRoot

42 GYEONGSAN `Born2beRoot` 과제를 진행하며 설치하고 설정한 내용을 정리한 README입니다.  
이번 문서는 단순한 설치 순서만 적는 대신, `왜 이런 설정을 하는지`와 `네트워크가 어떻게 동작하는지`까지 함께 이해할 수 있도록 정리했습니다.

## 프로젝트 목표

Born2beRoot는 가상머신 안에 ubuntu 서버를 직접 설치하고, 보안 정책과 계정 관리, 디스크 구성, 네트워크 설정까지 스스로 적용해보는 과제입니다.

이 과제를 통해 익히는 핵심은 다음과 같습니다.

- 가상머신 위에 서버 환경을 구축하는 방법
- Debian 기반 ubuntu 설치 과정
- 디스크 암호화와 `LVM` 구성
- `sudo`, `SSH`, `UFW` 같은 기본 보안 설정
- 사용자, 그룹, 비밀번호 정책 관리
- 크론을 이용한 시스템 모니터링 자동화

## 설치 환경

- Hypervisor: `VirtualBox`
- OS: `Debian`
- 설치 방식: GUI 없는 서버 환경
- 디스크 구성: `encrypted LVM`
- SSH 포트: `4242`

## 왜 VirtualBox를 쓰는가

Born2beRoot는 실제 PC를 건드리는 대신 가상머신 안에서 안전하게 서버를 구성하는 과제입니다.  
가상머신을 사용하면 운영체제를 새로 설치하고 파티션을 나누고 네트워크를 바꾸고 실수로 설정을 망가뜨려도 호스트 OS에는 영향을 주지 않습니다.

즉 VirtualBox는 "연습용 서버 컴퓨터를 내 컴퓨터 안에 하나 더 만드는 도구"라고 이해하면 됩니다.

## 왜 Debian을 선택했는가

Debian은 안정성이 높고 문서가 많아서 서버 운영 입문용으로 적합합니다.  
Born2beRoot에서는 Rocky 또는 Debian 중 하나를 선택하는 경우가 많은데, 저는 패키지 관리와 자료 접근성이 편한 Debian으로 진행했습니다.

## 디스크를 암호화하고 LVM을 쓰는 이유

### 디스크 암호화

디스크 암호화는 저장장치에 들어 있는 데이터를 바로 읽지 못하게 보호하는 설정입니다.  
가상머신 파일이 외부로 유출되더라도 암호 없이는 내부 데이터를 쉽게 볼 수 없게 만드는 역할을 합니다.

### LVM

`LVM(Logical Volume Manager)`은 디스크를 유연하게 관리하기 위한 구조입니다.  
단순히 디스크를 한 번 나누고 끝내는 방식보다 나중에 용량을 조절하거나 논리 볼륨을 관리하기 쉽다는 장점이 있습니다.

Born2beRoot에서 `LVM`을 요구하는 이유는 단순 사용법보다 "unbuntu에서 스토리지를 어떻게 구조적으로 나누는지"를 이해하게 하려는 의도가 크다고 느꼈습니다.

## 파티션을 나누는 이유

Born2beRoot에서는 보통 `/`, `/home`, `/var`, `/tmp`, `swap` 등을 분리합니다.

이렇게 나누는 이유는 각 영역의 역할이 다르기 때문입니다.

- `/`: 시스템 전체의 기준이 되는 루트 영역
- `/home`: 사용자 데이터 저장
- `/var`: 로그, 캐시, 서비스 데이터 저장
- `/tmp`: 임시 파일 저장
- `swap`: 메모리 부족 시 보조 영역

특히 `/var`와 `/tmp`를 분리하면 특정 영역이 과도하게 차서 시스템 전체에 영향을 주는 상황을 줄이는 데 도움이 됩니다.

## 설치 흐름

제가 진행한 전체 흐름은 아래와 같습니다.

1. `VirtualBox`에서 Debian 가상머신 생성
2. Debian 설치 시작
3. `encrypted LVM` 방식으로 디스크 구성
4. 사용자 계정과 hostname 설정
5. 설치 후 `sudo`, `SSH`, `UFW` 설정
6. 비밀번호 정책 적용
7. 사용자 그룹 추가 및 권한 정리
8. `cron`과 `monitoring.sh` 설정

## 기본 설정 정리

### 1. sudo 설치 및 권한 설정

`sudo`는 일반 사용자가 필요한 순간에만 관리자 권한을 빌려 쓰게 해주는 도구입니다.  
리눅스에서는 `root`를 항상 직접 사용하는 것보다 일반 계정으로 로그인한 뒤 필요한 명령만 `sudo`로 실행하는 방식이 더 안전합니다.

예시:

```bash
apt update
apt install sudo
usermod -aG sudo <username>
getent group sudo
```

이후 `sudoers` 설정을 통해 다음과 같은 보안 정책을 적용할 수 있습니다.

- 비밀번호 입력 기회 제한
- 잘못된 비밀번호 메시지 설정
- 로그 저장
- `tty` 기반 실행 강제
- 안전한 실행 경로 제한

### 2. SSH 설정

`SSH`는 원격으로 서버에 접속하기 위한 프로토콜입니다.  
Born2beRoot에서는 서버에 직접 붙는 것뿐 아니라 네트워크를 통해 접속 구조를 이해하는 것도 중요합니다.

주요 설정 흐름:

```bash
apt install openssh-server
systemctl status ssh
```

그리고 기본 포트 `22` 대신 과제 요구사항에 맞게 `4242` 포트로 변경합니다.

```bash
sudo nano /etc/ssh/sshd_config
```

설정 예시:

```text
Port 4242
PermitRootLogin no
```

여기서 중요한 점은 `root`의 직접 SSH 로그인을 막는 것입니다.  
관리자 권한이 필요하더라도 일반 사용자로 접속한 뒤 `sudo`를 사용하는 구조가 더 안전합니다.

### 3. UFW 방화벽 설정

`UFW`는 리눅스 방화벽을 비교적 쉽게 다룰 수 있게 만든 도구입니다.  
외부에서 서버로 들어오는 연결을 제한해 불필요한 접근을 막을 수 있습니다.

예시:

```bash
apt install ufw
ufw allow 4242
ufw enable
ufw status numbered
```

즉 "SSH는 허용하되 과제에서 정한 포트만 열어둔다"는 식으로 최소한의 통신만 허용하는 것이 핵심입니다.

## 네트워크를 이해하고 설정한 이유

Born2beRoot를 하면서 처음에는 "왜 포트포워딩이 필요한지"가 제일 헷갈렸습니다.  
그래서 아래처럼 개념을 정리하고 나니 SSH 연결 흐름이 훨씬 잘 이해됐습니다.

### 1. 사설 IP와 공인 IP

가상머신이나 내 컴퓨터는 보통 공유기 안쪽 네트워크에서 `192.168.x.x` 같은 사설 IP를 받습니다.  
이 주소는 같은 내부망 안에서만 의미가 있고 인터넷 바깥에서는 직접 접근할 수 없습니다.

반대로 공인 IP는 외부 인터넷에서 보이는 주소입니다.  
외부에서 내 네트워크로 들어오려면 결국 이 공인 IP를 거쳐야 합니다.

쉽게 말하면:

- 사설 IP: 건물 안의 호수
- 공인 IP: 건물의 도로명 주소

호수만 알아서는 외부인이 찾아올 수 없고 건물 주소와 연결 방식까지 알아야 접근할 수 있습니다.

### 2. NAT란

`NAT(Network Address Translation)`은 사설 IP와 공인 IP 사이를 변환해 주는 방식입니다.  
내부 네트워크의 여러 기기가 하나의 공인 IP를 공유하면서 인터넷에 나갈 수 있는 이유가 NAT 덕분입니다.

즉

- 내 VM은 사설 IP를 가짐
- 공유기나 VirtualBox 네트워크가 바깥과 연결될 때 주소를 변환함
- 그래서 외부에서는 VM의 사설 IP를 직접 볼 수 없음

이 개념 때문에 단순히 VM 안에서 SSH를 켠 것만으로는 호스트에서 바로 접근이 안 될 수 있습니다.

### 3. 포트란

IP가 "어느 컴퓨터인가"를 나타낸다면 포트는 "그 컴퓨터 안의 어떤 서비스인가"를 나타냅니다.

예를 들면:

- `127.0.0.1:4242`
- `192.168.0.10:80`

여기서 앞은 주소 뒤는 서비스의 문 번호라고 보면 이해하기 쉽습니다.

### 4. 포트 포워딩이란

포트 포워딩은 외부에서 들어온 특정 포트 요청을 내부의 특정 장치와 포트로 전달하는 설정입니다.

Born2beRoot에서 이게 필요한 이유는 다음과 같습니다.

- 가상머신은 내부 네트워크에 있음
- 호스트는 그 내부 VM에 직접 접근하기 어려울 수 있음
- 그래서 `호스트의 특정 포트 -> VM의 4242 포트`로 연결 규칙을 만들어야 함

예를 들어 VirtualBox에서 다음처럼 잡을 수 있습니다.

- Host Port: `4242`
- Guest Port: `4242`

그러면 호스트에서 아래처럼 접속할 수 있습니다.

```bash
ssh <username>@127.0.0.1 -p 4242
```

즉 내가 접속하는 대상은 표면적으로는 `127.0.0.1:4242` 이지만 실제로는 포트 포워딩 규칙을 따라 가상머신 안의 SSH 서버로 연결되는 구조입니다.

## 비밀번호 정책

Born2beRoot는 단순히 비밀번호를 만드는 수준이 아니라 "강한 비밀번호 규칙을 시스템에 강제"하는 것이 중요합니다.

보통 다음 정책을 적용합니다.

- 최소 길이 설정
- 대문자 포함
- 숫자 포함
- 동일 문자 반복 제한
- 이전 비밀번호와 충분히 다르게 설정
- 비밀번호 변경 주기 설정
- 만료 전 경고 일수 설정

관련 설정 파일은 주로 아래 두 곳입니다.

- `/etc/pam.d/common-password`
- `/etc/login.defs`

예시로 확인한 값:

```text
PASS_MAX_DAYS 30
PASS_MIN_DAYS 2
PASS_WARN_AGE 7
```

이 설정은 "비밀번호를 자주 바꾸게 하고 너무 쉽게 바꾸거나 약하게 바꾸지 못하게 하는 것"에 목적이 있습니다.

## 그룹과 사용자 관리

과제에서는 사용자와 그룹을 직접 만들고 적절한 권한을 부여할 수 있어야 합니다.

예시:

```bash
groupadd user42
groupadd evaluating
usermod -aG user42 <username>
usermod -aG evaluating <evaluation_user>
getent group user42
getent group evaluating
groups <username>
```

이 과정은 단순히 계정 하나 만드는 일이 아니라 "어떤 사용자가 어떤 역할을 가지는가"를 구분하는 권한 관리 연습에 가깝습니다.

## sudo 정책

Born2beRoot에서는 `sudo` 사용 자체도 과제 평가 포인트입니다.  
보통 아래 같은 조건을 맞춥니다.

- 비밀번호 입력 실패 허용 횟수 제한
- 잘못된 비밀번호 경고 메시지 설정
- 모든 sudo 동작 로그 저장
- `requiretty` 적용
- 안전한 `secure_path` 설정

예시:

```text
Defaults passwd_tries=3
Defaults badpass_message="Password is wrong please try again!"
Defaults logfile="/var/log/sudo/sudo.log"
Defaults log_inputlog_output
Defaults requiretty
Defaults secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
```

## hostname과 hosts 설정

호스트네임은 서버의 이름입니다.  
평가 중에는 hostname 변경과 확인을 직접 요구하는 경우가 있으므로 기본 개념을 알아두는 것이 좋습니다.

```bash
hostnamectl
hostnamectl set-hostname <new_hostname>
sudo nano /etc/hosts
```

`/etc/hosts`에서도 기존 hostname을 함께 수정해 주어야 이름 해석이 어긋나지 않습니다.

## monitoring.sh와 cron

Born2beRoot의 마지막 핵심은 시스템 상태를 주기적으로 출력하는 스크립트를 만드는 것입니다.  
이 스크립트는 보통 `wall` 명령으로 모든 터미널에 시스템 정보를 방송합니다.

여기에 포함되는 정보 예시는 다음과 같습니다.

- 운영체제와 커널 정보
- 물리 CPU / vCPU 수
- 메모리 사용량
- 디스크 사용량
- CPU 부하
- 마지막 부팅 시각
- LVM 사용 여부
- TCP 연결 수
- 로그인 사용자 수
- IP 주소와 MAC 주소
- sudo 사용 횟수

그리고 `cron`을 이용해 10분마다 실행되도록 등록합니다.

```bash
sudo crontab -u root -e
```

예시:

```cron
*/10 * * * * /usr/local/bin/monitoring.sh
```

## 평가에서 확인할 것

제가 정리한 체크 포인트는 아래와 같습니다.

- Debian 기반으로 설치했는가
- GUI 없이 운영되는가
- `LVM`이 적용되어 있는가
- 디스크 암호화가 적용되어 있는가
- `SSH`가 `4242` 포트에서 동작하는가
- `root` SSH 로그인이 막혀 있는가
- `UFW`가 활성화되어 있고 필요한 포트만 열려 있는가
- 비밀번호 정책이 적용되어 있는가
- `sudo` 정책과 로그 설정이 되어 있는가
- 사용자와 그룹이 과제 요구사항에 맞게 생성되어 있는가
- `monitoring.sh`가 주기적으로 실행되는가

## 느낀 점

Born2beRoot는 "리눅스 설치 과제"라기보다 서버를 운영할 때 어떤 기준으로 보안과 구조를 잡아야 하는지 처음부터 끝까지 경험해보는 과제에 가깝다고 느꼈습니다.

특히 아래 개념이 많이 남았습니다.

- 단순 설치보다 설정 이유를 이해하는 것이 더 중요하다는 점
- 사설 IP NAT 포트 포워딩을 알아야 SSH 구조가 보인다는 점
- root를 직접 쓰지 않고 권한을 분리하는 것이 왜 중요한지
- 파티션과 LVM이 운영 안정성과 연결된다는 점

## 참고 자료

- Medium: [Born2beroot. 42 school project](https://baigal.medium.com/born2beroot-e6e26dfb50ac)
- Tistory: [NAT 쉽게 이해하기](https://aws-hyoh.tistory.com/145)
- Tistory: [IP주소와 포트포워딩이란 포트포워딩 설정하기(iptime)](https://hyunie-y.tistory.com/23)
