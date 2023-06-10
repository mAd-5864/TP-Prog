void encontra_paragens_percursos(paragem *vparagem, int n)
{
    int partidaEncontrada = 0, chegadaEncontrada = 0, percursoEncontrado = 0;
    percursos percurso;

    // Verifica se existem paragens
    if (n == 0)
    {
        printf("\nNao existem paragens registadas\n");
        return;
    }

    printf("\nNome da paragem de partida:\n");
    scanf(" %[^\n]", percurso.paragem_partida);

    printf("\nNome da paragem de chegada:\n");
    scanf(" %[^\n]", percurso.paragem_chegada);

    while (linhaAtual != NULL)
    {
        Linha *linha = &(linhaAtual->linha);
        ParagemLinha *paragemAtual = linha->primeiraParagem;

        // Verificar se viagem e possivel na linha
        while (paragemAtual != NULL)
        {
            i++;
            if (strcmp(paragemAtual->paragem.nome, percurso.paragem_partida) == 0)
            {
                partidaEncontrada = 1;
            }
            if (strcmp(paragemAtual->paragem.nome, percurso.paragem_chegada) == 0)
            {
                chegadaEncontrada = 1;
            }

            if (partidaEncontrada && chegadaEncontrada)
            {
                // Percurso encontrado
                break;
            }

            paragemAtual = paragemAtual->proximaParagem;
        }
        if (!percursoEncontrado)
        {
            printf("\nNao existe percurso direto\n\n");
        }

        linhaAtual = linhaAtual->proximaLinha;
    }
}