## Classificação e Pesquisa de Dados
## Trabalho Final

### To-do list

- [ ] Criar estruturas de hash table
- [ ] Criar rotinas da fase 1
- [ ] Criar estruturas de árvore trie para pesquisa
- [ ] Criar rotina para receber comandos de pesquisa
- [ ] Criar pesquisa "player"
- [ ] Criar pesquisa "user"
- [ ] Criar pesquisa "top&lt;N&gt;"
- [ ] Criar pesquisa "tags"

### Pontos principais

- Fase 1:
  - Fase de construção e inicialização das estruturas de dados
  - Abertura de arquivos só pode ser feita nesta etapa
  - Deve demorar menos de 3 minutos (menos de 1 minutos == bônus de 10%)
- Fase 2:
  - Modo console (pesquisas)
  - player &lt;name or prefix&gt;
    - `$ player Fer`
    - Retorna a lista de jogadores cujo nome começa ou é igual ao texto fornecido (id, nome, posições, avaliação média e número de avaliações)
    - Utiliza *árvore trie* para buscar os identificadores
  - user &lt;userID&gt;
    - `$ user 4`
    - Retorna a lista com no máximo 20 jogadores revisados pelo usuário
    - Mostrar id, nome, média global, quantidade de avaliações e avaliação dada pelo usuário
    - Ordenar decrescente pela nota dada pelo usuário
    - Criar estrutura de dados para armazenar essas informações por usuário
  - top&lt;N&gt; '&lt;position&gt;'
    - `$ top10 'ST'`
    - Retorna a lista dos N jogadores com melhores notas de uma posição
    - Considera apenas jogadores com no mínimo 1000 avaliações
    - Ordenar da maior para a menor avaliação
  - tags &lt;list of tags&gt;
    - `$ tags 'Brazil' 'Dribble'`
    - Retorna a lista de jogadores que estão associados ao conjunto de tags fornecido
    - Criar estrutura de dados para armazenar e buscar essas informações
- Interfaces gráficas e novas consultas serão recompensadas com até 20% de nota extra
