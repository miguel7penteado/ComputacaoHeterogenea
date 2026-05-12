# Computação Heterogênea para DataScience


## SYSCL - Framework para Computação Heterogênea

**SYCL** é um padrão de programação paralela para **C++ moderno**.

Ele permite escrever programas que executam partes do código em diferentes tipos de hardware, como:

| Hardware     | Exemplo                |
| ------------ | ---------------------- |
| CPU          | Processador principal  |
| GPU          | Placa de vídeo         |
| FPGA         | Circuito programável   |
| Aceleradores | Hardware especializado |

A ideia principal do **SYCL** é permitir que o programador escreva código em **C++**, usando uma única linguagem, para executar tarefas em paralelo em vários dispositivos.

Em vez de escrever código separado para cada tipo de hardware, o SYCL oferece uma forma mais portável de programação paralela.

Exemplo conceitual:

```cpp
q.parallel_for(
	range<1>(n), [=](id<1> i) 
	{
		c[i] = a[i] + b[i];
	}
);
```

Nesse exemplo, o comando `parallel_for` indica que a operação será executada em paralelo. Cada posição dos vetores `a`, `b` e `c` pode ser processada simultaneamente.

Em resumo:

> **SYCL é um modelo de programação paralela em C++ que permite usar CPUs, GPUs e outros aceleradores de forma portável.**


## 

Sim. **DPC++** significa **Data Parallel C++**.

Ele é, essencialmente, um **compilador C++ baseado no ecossistema Clang/LLVM**, com extensões e suporte para **SYCL**, usado principalmente no ambiente **Intel oneAPI** para programação paralela em CPUs, GPUs e outros aceleradores.

Uma forma simples de entender é:

```text
LLVM
 └── Clang / clang++
      └── DPC++ / dpcpp / icpx
            └── C++ com suporte a SYCL
```

## O que é DPC++?

O **DPC++** é uma implementação de C++ voltada à **programação paralela heterogênea**. Isso significa que o mesmo programa pode ser escrito para executar em diferentes tipos de hardware, como:

| Hardware            | Exemplo                                          |
| ------------------- | ------------------------------------------------ |
| CPU                 | Processadores Intel, AMD etc.                    |
| GPU                 | GPUs Intel, NVIDIA ou AMD, dependendo do backend |
| FPGA                | Aceleradores programáveis                        |
| Outros aceleradores | Dispositivos especializados                      |

O objetivo é permitir que o programador escreva código C++ moderno e envie partes desse código para execução paralela em dispositivos aceleradores.

### Relação de DPC++ com Clang++ e LLVM

O DPC++ não é um compilador totalmente isolado. Ele deriva da infraestrutura do **Clang/LLVM**.

| Componente  | Função                                      |
| ----------- | ------------------------------------------- |
| **LLVM**    | Infraestrutura de compilação e otimização   |
| **Clang++** | Compilador C++ baseado em LLVM              |
| **DPC++**   | Compilador C++ com suporte adicional a SYCL |
| **SYCL**    | Modelo de programação paralela em C++       |

Ou seja, o DPC++ pode ser entendido como uma versão estendida do `clang++`, preparada para compilar programas que usam SYCL.

### Relação de DPC++ com SYCL?

**SYCL** é um padrão de programação paralela em C++ que permite escrever código para dispositivos como CPUs, GPUs e aceleradores.

Enquanto em CUDA o código normalmente é voltado principalmente para GPUs NVIDIA, o SYCL busca ser mais portável.

Comparação simplificada:

| Tecnologia | Principal foco                             |
| ---------- | ------------------------------------------ |
| CUDA       | GPUs NVIDIA                                |
| OpenCL     | Programação heterogênea em C/C++           |
| SYCL       | Programação heterogênea usando C++ moderno |
| DPC++      | Implementação de C++/SYCL baseada em LLVM  |

## Exemplo conceitual

Em C++ tradicional:

```cpp
for (int i = 0; i < n; i++) 
{
    c[i] = a[i] + b[i];
}
```

Com SYCL/DPC++, essa operação pode ser enviada para execução paralela em uma GPU ou outro acelerador:

```cpp
q.parallel_for(
	range<1>(n), [=](id<1> i) 
	{
		c[i] = a[i] + b[i];
	}
);
```

Aqui, `parallel_for` indica que várias iterações podem ser executadas em paralelo.

### resumindo DPC++

**DPC++ é um compilador C++ baseado em Clang/LLVM, criado para compilar programas C++ com SYCL, permitindo programação paralela em CPUs, GPUs e aceleradores.**

Uma definição curta seria:

> **DPC++ é uma extensão do C++ moderno, baseada em Clang/LLVM, voltada à programação paralela heterogênea usando SYCL.**


## hipSYCL (AdaptiveCpp) - Uma impantação SYSCL aberta

**hipSYCL** foi uma implementação livre e independente do padrão **SYCL** para programação heterogênea em **C++**, isto é, para escrever um único código C++ capaz de executar em **CPU** e também em **GPUs** de diferentes fabricantes.

Hoje, o projeto é conhecido principalmente como **AdaptiveCpp**. Antes disso, também foi chamado de **Open SYCL**. A própria página do projeto informa que o AdaptiveCpp era anteriormente conhecido como **hipSYCL / Open SYCL**. ([GitHub][1])

Em termos simples:

> **hipSYCL / AdaptiveCpp é uma implementação de SYCL que permite programar CPUs e GPUs usando C++, com suporte a diferentes backends como CUDA, HIP/ROCm, OpenMP, OpenCL e Level Zero.**

## Relação com SYCL

**SYCL** é um padrão da Khronos para programação paralela heterogênea em C++. Ele permite escrever código “single-source”, ou seja, código do host e do dispositivo no mesmo programa C++.

Exemplo conceitual:

```cpp
q.parallel_for(
	range<1>(N), [=](id<1> i) 
	{
		C[i] = A[i] + B[i];
	}
);
```

Esse kernel pode ser executado em uma GPU ou CPU, dependendo da implementação SYCL usada.

## O que hipSYCL original fazia

O hipSYCL fornecia:

1. **Compilador e runtime SYCL**

   Ele permitia compilar programas escritos em SYCL e executá-los em diferentes arquiteturas.

2. **Suporte a vários backends**

   O projeto passou a suportar plataformas como **CUDA**, **HIP/ROCm**, **OpenMP**, **OpenCL** e **Level Zero**, permitindo usar GPUs NVIDIA, AMD, Intel e CPUs. ([Julia Programming Language][2])

3. **Portabilidade**

   A ideia era reduzir a dependência de uma única tecnologia, como CUDA, que é fortemente associada ao ecossistema NVIDIA.

4. **Modelo baseado em biblioteca + compilador**

   Ele se apoiava fortemente em C++ moderno, bibliotecas e infraestrutura de compilação baseada em LLVM/Clang.

## Por que adição do nome “hip”

O nome **hipSYCL** fazia referência ao **HIP**, que é a camada de programação da AMD/ROCm semelhante ao CUDA. A proposta inicial era permitir que código SYCL pudesse ser executado sobre backends como **HIP** e **CUDA**, aproximando o ecossistema SYCL das GPUs AMD e NVIDIA.

Depois, o escopo ficou maior, passando a incluir mais backends e mais modelos de programação. Por isso, o nome mudou para **AdaptiveCpp**.

## Tabela comparativa

| Tecnologia                | O que é                            | Foco principal                                    |
| ------------------------- | ---------------------------------- | ------------------------------------------------- |
| **CUDA**                  | Plataforma da NVIDIA para GPU      | GPUs NVIDIA                                       |
| **HIP/ROCm**              | Plataforma da AMD para GPU         | GPUs AMD, com compatibilidade conceitual com CUDA |
| **SYCL**                  | Padrão C++ da Khronos              | Código portável para CPU/GPU                      |
| **DPC++**                 | Implementação SYCL da Intel/oneAPI | Intel, mas também com outros backends             |
| **hipSYCL / AdaptiveCpp** | Implementação independente de SYCL | Portabilidade entre NVIDIA, AMD, Intel e CPU      |


**hipSYCL**, atualmente **AdaptiveCpp**, é uma implementação de **SYCL** que permite escrever programas paralelos em **C++** para executar em diferentes hardwares, como CPUs e GPUs NVIDIA, AMD e Intel, sem prender o código a uma única plataforma como CUDA.



## Numba - Compilador para Python

**Numba** é um compilador **JIT** (*Just-In-Time*) para Python, usado principalmente para acelerar programas numéricos e científicos.

Em vez de interpretar o código Python linha por linha, o Numba compila partes do código em **código de máquina otimizado**, usando infraestrutura baseada em **LLVM**. Ele é especialmente eficiente quando o código usa **NumPy**, laços `for`, vetores, matrizes e cálculos matemáticos intensivos. A documentação oficial descreve o Numba como um compilador JIT aberto que traduz um subconjunto de Python e NumPy para código de máquina rápido. ([Numba][1])

### Objetivo

Em Python puro, um laço numérico pode ser lento:

```python
def soma_vetor(v):
    soma = 0
    for i in range(len(v)):
        soma += v[i]
    return soma
```

Com Numba, podemos compilar essa função:

```python
from numba import njit

@njit
def soma_vetor(v):
    soma = 0
    for i in range(len(v)):
        soma += v[i]
    return soma
```

O decorador `@njit` pede ao Numba para compilar a função para código de máquina.

### Utilidade

O Numba é útil quando temos:

| Situação                  | Benefício                               |
| ------------------------- | --------------------------------------- |
| Laços numéricos grandes   | Execução muito mais rápida              |
| Cálculo com arrays NumPy  | Otimização automática                   |
| Simulações científicas    | Melhor desempenho                       |
| Processamento de matrizes | Uso eficiente da CPU                    |
| Programação paralela      | Possibilidade de usar múltiplos núcleos |
| GPU NVIDIA                | Possibilidade de gerar código CUDA      |

### Programação paralela com Numba

O Numba também pode paralelizar laços usando `parallel=True` e `prange`:

```python
from numba import njit, prange

@njit(parallel=True)
def dobrar_vetor(v):
    resultado = v.copy()

    for i in prange(len(v)):
        resultado[i] = v[i] * 2

    return resultado
```

Aqui, `prange` funciona como um `range` paralelo. O trabalho pode ser dividido entre vários núcleos da CPU.

### Numba e a GPU (nvidia CUDA)

O Numba também possui suporte para geração de código acelerado por GPU, principalmente com **CUDA**, permitindo escrever kernels em Python para execução em GPUs NVIDIA. A página do projeto informa que o Numba possui suporte para paralelização automática, código acelerado por GPU e criação de funções universais NumPy, entre outros recursos. ([GitHub][2])

Exemplo conceitual com CUDA:

```python
from numba import cuda

@cuda.jit
def soma_gpu(a, b, c):
    i = cuda.grid(1)

    if i < c.size:
        c[i] = a[i] + b[i]
```

Nesse caso, a função `soma_gpu` é executada na GPU.

### Tabela comparativa

| Tecnologia                | Linguagem          | Objetivo                           |
| ------------------------- | ------------------ | ---------------------------------- |
| **Numba**                 | Python             | Acelerar código Python/NumPy       |
| **Cython**                | Python + sintaxe C | Gerar extensões C para Python      |
| **CUDA**                  | C/C++/Python       | Programação de GPUs NVIDIA         |
| **CuPy**                  | Python             | NumPy acelerado em GPU             |
| **SYCL**                  | C++                | Programação heterogênea portável   |
| **DPC++**                 | C++                | Implementação SYCL da Intel        |
| **hipSYCL / AdaptiveCpp** | C++                | Implementação SYCL multiplataforma |


**Numba é um compilador JIT para Python que transforma funções numéricas em código de máquina rápido, permitindo acelerar cálculos em CPU e, em alguns casos, em GPU, com poucas alterações no código Python.**

## DPCTL - Controle Paralo de Dados em Python

**DPCTL** significa **Data Parallel Control**.

Ele é uma biblioteca Python que fornece **ligações Python para classes do SYCL**, ou seja, uma forma de acessar, a partir do Python, elementos do modelo de programação **SYCL/oneAPI**, como:

| Recurso SYCL                | Uso no DPCTL                                           |
| --------------------------- | ------------------------------------------------------ |
| `sycl::device`              | Representar CPU, GPU ou acelerador                     |
| `sycl::platform`            | Consultar plataformas disponíveis                      |
| `sycl::context`             | Criar contexto de execução                             |
| `sycl::queue`               | Enviar tarefas para um dispositivo                     |
| USM — Unified Shared Memory | Alocar memória compartilhável entre host e dispositivo |

A documentação oficial descreve o `dpctl` como uma biblioteca que fornece ligações em **C** e **Python** para recursos do **SYCL 2020**, especialmente classes de runtime e alocadores de memória USM. ([intelpython.github.io][1])

### Objetivo

O **SYCL** é originalmente usado em **C++**. O DPCTL permite controlar parte desse ambiente a partir do **Python**.

Em outras palavras:

> **DPCTL é uma camada Python sobre SYCL, usada para selecionar dispositivos, criar filas de execução, controlar memória e integrar Python ao ecossistema oneAPI/SYCL.**

### Exemplo

Com DPCTL, é possível consultar dispositivos disponíveis:

```python
import dpctl

devices = dpctl.get_devices()

for device in devices:
    print(device)
```

Também é possível criar uma fila SYCL:

```python
import dpctl

queue = dpctl.SyclQueue("gpu")
print(queue.sycl_device)
```

Essa fila representa um canal para enviar operações para uma GPU, CPU ou outro acelerador compatível.

### ecossistema

O DPCTL não é exatamente equivalente ao Numba. Ele atua em uma camada mais próxima do **controle de dispositivos SYCL**.

| Ferramenta       | Linguagem | Papel                                        |
| ---------------- | --------- | -------------------------------------------- |
| **DPC++**        | C++       | Compilador C++ com suporte SYCL              |
| **SYCL**         | C++       | Modelo de programação heterogênea            |
| **DPCTL**        | Python    | Ligações Python para classes SYCL            |
| **Numba**        | Python    | Compilação JIT para código numérico/paralelo |
| **dpctl.tensor** | Python    | Arrays/tensores usando memória SYCL/USM      |

A própria página do oneAPI Open Source resume o DPCTL como **“Python bindings for SYCL classes”**. ([oneAPI][2])

### O DPCTL e o `dpctl.tensor`

Além das classes básicas de controle, o projeto também possui o módulo **`dpctl.tensor`**, que fornece arrays/tensores em Python usando memória **USM** de SYCL. Segundo a Intel, `dpctl.tensor` é implementado em SYCL puro e construído com o compilador Intel oneAPI DPC++. ([Intel][3])

Exemplo conceitual:

```python
import dpctl.tensor as dpt

x = dpt.arange(10, dtype="float32", device="gpu")
y = x * 2

print(y)
```

Aqui, a ideia é parecida com NumPy, mas os dados podem estar associados a um dispositivo SYCL, como GPU ou CPU.

**DPCTL é uma biblioteca Python que permite controlar dispositivos SYCL — como CPUs, GPUs e aceleradores — criando filas, contextos e memória USM, funcionando como uma ponte entre Python e o ecossistema oneAPI/SYCL.**





[1]: https://intelpython.github.io/dpctl/0.8.0/index.html?utm_source=chatgpt.com "Welcome to Data-parallel Control (dpctl)'s documentation!"
[2]: https://oneapi.io/open-source/?utm_source=chatgpt.com "oneAPI Open Source"
[3]: https://www.intel.com/content/www/us/en/developer/articles/technical/ext-for-python-accel-computations-leverage-gpus.html?utm_source=chatgpt.com "Portable Data Parallel Extensions for Python Language"


## REFERÊNCIAS

[1]: https://numba.pydata.org/?utm_source=chatgpt.com "Numba: A High Performance Python Compiler"
[2]: https://github.com/numba/numba?utm_source=chatgpt.com "Numba - NumPy aware dynamic Python compiler using ..."


[1]: https://github.com/AdaptiveCpp/AdaptiveCpp?utm_source=chatgpt.com "AdaptiveCpp (formerly known as hipSYCL / Open SYCL)"
[2]: https://discourse.julialang.org/t/adaptivecpp-integration/129070?utm_source=chatgpt.com "AdaptiveCpp integration? - GPU"




[![Linkedin](https://i.stack.imgur.com/gVE0j.png) LinkedIn](https://www.linkedin.com/in/miguel-penteado-760486a9/)
&nbsp;
[![GitHub](https://i.stack.imgur.com/tskMh.png) GitHub](https://github.com/miguel7penteado)
