# Benternet Translation Service

The Benternet Translation Service is a lightweight and efficient service designed to translate text messages sent over a ZeroMQ network. It utilizes ZeroMQ messaging patterns to seamlessly integrate with various applications and systems requiring translation capabilities. This documentation provides a comprehensive guide on setting up, configuring, and utilizing the service.

## Features

- Real-time Translation: Translate text messages in real-time as they are sent over the network.
- AI language detection: Detect the language of the text to be translated
- Dockerized Translation Engine: Utilizes a Docker container running LibreTranslate for language translation.
- ZeroMQ Integration: Seamlessly integrates with ZeroMQ messaging patterns for robust and scalable communication.
- Customizable: Easily configurable to adapt to different translation requirements and environments.

## Index

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Diagram](#diagram)

## Prerequisites

- Working [gcc compiler](https://gcc.gnu.org/)
- ZeroMQ [cppzmq](https://github.com/zeromq/cppzmq) Library
- [Docker](https://docs.docker.com/get-docker/) (engine or desktop)

Optional:
- Qt Creator
- git

## Installation and Setup

Clone the repo to a local folder
Use the download button or the shell command
```shell
git clone https://github.com/RobbeTh-PXL/Benternet_Service.git

```

### LibreTranslate

**Refer to the [official LibreTranslate documentation](https://github.com/LibreTranslate/LibreTranslate) for package options and support**

1. In a shell, open the cloned folder "Benternet_Service/LibreTranslate-main":

```shell
cd Benternet_Service/LibreTranslate-main/
```

2. Run the startup script with the required execute permission:

**Windows**
```shell
run.bat [args]
```

**Linux/macOS**
```shell
./runs.sh [args]
```

### Benternet ZeroMQ

Download the [prebuild binaries]() or compile from source

#### Compile from source

Open Benternet_Service/Benternet_Service.pro in Qt Creator

## Usage

1. Connect to the ZeroMQ network with a suitable client
2. Request the Translation Service with the following format:
```shell
translate?>[username]>[source language]-[target language]>[text to translate]
```
To use the AI language detection, use **auto** as "source language"

**Example**
```shell
translate?>john>auto-nl>Hello world!
```

3. The service will output its response to:
```shell
translate!>[username]>"Response"
```

**Example Output**
```shell
translate!>john>Hallo wereld!
```

## Commands

In order to use commands, the request format differs:
```shell
translate?>[username]>[command]>[input]
```

A list of commands:
- langs     -> Returns a list of available/supported languages
- detect    -> Detects the language of "input"

### Translate commands

Optionally a command can be specified after "text to translate"
```shell
translate?>[username]>[source language]-[target language]>[text to translate]>[translate command]
```

A list of translate commands:
- spellcheck    -> Check and correct the spelling of the "text to translate"

## Diagram
