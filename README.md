# Cadastro de Pedidos de Venda em C

Um sistema em linguagem C para gerenciamento de **itens**, **estoque** e **pedidos de venda**, com funcionalidades de cadastro, consulta e controle de disponibilidade de produtos.

---

## Funcionalidades Principais

O sistema oferece as seguintes operações:

#### Cadastro de Itens
- Permite adicionar novos itens ao catálogo  
- Armazena código, descrição e preço unitário  

#### Entrada de Estoque
- Atualiza a quantidade disponível de itens  
- Controla e registra novos recebimentos  

#### Cadastro de Pedidos
- Cria pedidos de venda  
- Valida se o item existe e se há estoque disponível  
- Atualiza automaticamente o saldo do estoque ao efetivar o pedido  

#### Listagem e Consultas 
- Lista todos os itens cadastrados  
- Lista todos os pedidos realizados  
- Permite busca por código de item ou pedido  

---

## Estrutura do Sistema

O sistema segue uma arquitetura simples, baseada em vetores e structs:

```c
typedef struct {
    char code[7];
    char name[50];
    float value;
    int available;
} Item;
```

```c
typedef struct {
    int unsigned id;
    char itemCode[7];
    int unsigned quantity;
    float orderTotal;
} Order;
```

### Validações Essenciais

Para garantir integridade, diversas validações são feitas automaticamente:

<table border="#002 1px solid">
  <tr>
    <th>Ação</th>
    <th>Validação</th>
  </tr>
  <tr>
    <td>Cadastro de item</td>
    <td>Verifica duplicidade de código</td>
  </tr>
  <tr>
    <td>Entrada de estoque</td>
    <td>Confere existência do item</td>
  </tr>
  <tr>
    <td>Criação de pedido</td>
    <td>Valida item + estoque disponível</td>
  </tr>
</table>
