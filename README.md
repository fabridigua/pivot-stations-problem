# Pivot Stations Problem

Questo repository  contiene la risoluzione al *Pivot Stations Problem*.

Di seguito l'analisi del problema e della risoluzione.

Linguaggio utilizzato: **C++ 14**

----

#### Definizioni

###### Movement Graph 

Si tratta di un grado diretto aciclico (DAG), che rappresenta tutti i possibili percorsi compiuti da un treno.
I nodi del grafo rappresentano le stazioni, mentre gli archi i possibili tratti del percorso che collegano due stazioni.
Ci possono essere situazioni in cui il treno può dover scegliere tra più tratti per raggiungere la stazione successiva.

###### Pivot Station

Si tratta di una stazione che, a prescindere dal percorso scelto del treno per andare da S_o a S_d, non può essere bypassata. 
In altre parole, tale stazione sarà presente in tutti i percorsi possibili tra S_o e S_d.
**Nota**: per semplicità, considero come Pivot Station anche la stazione di partenza e quella di arrivo.

---

#### Problema

Dato un Movement Graph m, una stazione di partenza S_o e una destinazione S_d, trovare le Pivot Stations del grafo.

---

#### Implementazione

- Inizialmente mi sono concentrato sulla definizione del Movement Graph: ho creato una classe che rappresenta il grafo tramite una lista di Station, una struttura che include un id numerico e una lista di possibili Track, che collegano la stazione ad un'altra stazione specificata.
- In seguito ho definito la ricerca dei percorsi possibili da una stazione di partenza ad una di arrivo, implementando l'algoritmo di Depth First Search, che ricorsivamente visita ciascun nodo (stazione) del grafo, analizzandone gli archi (i track) costruendo la lista di percorsi, con un principio simile agli algoritmi di backtracking, ovvero torna indietro nel percorso, aggiungendoci nuovi nodi raggiungibili per vedere se si può arrivare alla destinazione.
- Ho infine implementato due strategie per la ricerca delle Pivot Station dati S_o, S_d e la lista di percorsi possibili:
  - **Strategia 1**: 
    Una volta trovati i percorsi che portano da S_o a S_d, cerco le stazioni che sono presenti in tutti i percorsi.
  - Strategia 2:
    Elimino una alla volta le stazioni del grafo e cerco i percorsi da S_o a S_d: se non ne trovo la stazione eliminata è pivot.



#### Esecuzione

Nell'esempio del testo, senza considerare le stazioni di partenza e arrivo (S_0 e S_6) non sono presenti altre Pivot Station:

![](.\movement_graph_esempio_1.png)

Esecuzione algoritmo:
`[Strategy 1] Pivot Stations found between S0 and S6:`
`S0`
`S6`

`[Strategy 2] Pivot Stations found between S0 and S6:`
`S0`
`S6`

Tuttavia se elimino **T_12**, la stazione S_5 diventa una Pivot Station:

![](.\movement_graph_esempio_1_noT12.png)

Esecuzione:

`[Strategy 1] Pivot Stations found between S0 and S6:`
`S0`
`S5`
`S6`

`[Strategy 2] Pivot Stations found between S0 and S6:`
`S0`
`S5`
`S6`



Per testare maggiormente il codice ho costruito un'ulteriore Movement Graph, leggermente più complesso:

![](.\movement_graph_esempio_2.png)

in cui mi aspetto che le stazioni pivot siano S_o, S_1, S_6, S_7 e S_10. Infatti:

`[Strategy 1] Pivot Stations found between S0 and S10:`
`S0`
`S1`
`S6`
`S7`
`S10`

`[Strategy 2] Pivot Stations found between S0 and S10:`
`S0`
`S1`
`S6`
`S7`
`S10`



#### Analisi complessità

L'algoritmo di DFS da sè ha complessità ...

Strategia 1:

Strategia 2: dfs decrescente



