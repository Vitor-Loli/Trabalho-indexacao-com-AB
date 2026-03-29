# 🌳 Sistema de Indexação com Árvores Binárias


## 📋 Sobre o Projeto

Uma plataforma de e-commerce enfrenta gargalos em consultas complexas sobre seu catálogo de produtos. A solução proposta é um **sistema de indexação dupla** utilizando duas BSTs (Binary Search Trees) sincronizadas:

- **BST por ID** — índice primário para buscas exatas e únicas
- **BST por Preço** — índice secundário para consultas por faixa de valores e vizinho mais próximo

Ambas as árvores compartilham os mesmos nós de produto e devem permanecer **consistentes** entre si em todas as operações.

---

## ⚙️ Operações Implementadas

| Operação | Descrição |
|---|---|
| `inserir(produto)` | Insere nas duas árvores simultaneamente |
| `remover(id)` | Remove das duas árvores de forma consistente |
| `buscarPorId(id)` | Busca exata pela árvore de ID — O(log n) |
| `buscarPorFaixa(min, max)` | Retorna todos os produtos dentro de uma faixa de preço |
| `vizinhoMaisProximo(preco)` | Retorna o produto com preço mais próximo do valor informado |

---

## 🧪 Entrada de Teste

```
(50, "Mouse",    100.00)
(30, "Teclado",  150.00)
(70, "Monitor",  900.00)
(20, "Mousepad",  50.00)
(40, "Headset",  250.00)
(60, "Webcam",   300.00)
(80, "Notebook", 3500.00)
```

**Exemplo de consulta por faixa:** produtos entre R$ 200,00 e R$ 800,00  
→ Retorna: Headset (250), Webcam (300)

**Exemplo de vizinho mais próximo:** preço X = 400  
→ Retorna: Webcam (300) — diferença de 100




## 📜 Licença

Projeto desenvolvido para fins acadêmicos.
