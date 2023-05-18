# column_formatter

<!--
#field
Learning

#groups
Sapienza

#languages
C

#frames and libs

-->

OS 2 Homework

There are two versions of the program, one of them is multi process.
The difference between the single process and the multi process is that are present some wrapping functions
for the normal ones to implement a simple pipeline between the three sub-processes.

## Quick Commands

To compile:
```
make
```

To clean the compiled binary and the object files:
```
make fclean
```

To clean only objects:
```
make clean
```

To geterate a webpage with docs:
```
make docs
```

To generate the latex too:
```
make latex
```

To launch a quick test:
```
make test  # launches tester.sh
make val   # launches a test with valgrind
```

## Usage

```
./column_formatter columns_per_page columns_height columns_width columns_distance [in_file] [out_file]
```
if ```in_file``` not specified it will be ```stdin```

if ```out_file``` not specified it will be ```stdout```

## Example

```
./column_formatter 3 40 20 5 tests/example.txt
```

Input (tests/example.txt):
```
Sistemi Operativi II Modulo. Progetto (Homework).

L’obiettivo è implementare un programma C che trasformi un testo in italiano da una colonna a più colonne su più pagine (come ad es. per una pagina di quotidiano). Sono richieste due versioni del programma: una a singolo processo e una multi-processo con almeno tre processi concorrenti.

Dati in ingresso e requisiti: un file di testo in codifica Unicode (UTF-8) contenente un testo in italiano strutturato in paragrafi separati da una o più linee vuote (stringa contenente solo il carattere ‘\n’). Ogni paragrafo è  costituito da una o più stringhe terminate da ‘\n’ (il testo in ingresso è tutto su una sola colonna); il numero di colonne per pagina su cui distribuire il testo; il numero di linee per ogni colonna; larghezza di ogni colonna (numero di caratteri per colonna); la distanza in caratteri tra una colonna di testo e l’altra.

Dati in uscita e requisiti: un file di testo ASCII contenente il testo di input incolonnato e impaginato secondo i parametri espressi dall’utente. Le pagine sono separate dalla stringa “\n %%% \n”; ogni paragrafo è separato da una linea vuota; la prima colonna di testo è a sinistra; tutte le righe, tranne l’ultima, di ogni paragrafo dovranno essere allineate ad entrambi i margini della colonna; l’ultima riga di ogni paragrafo è solo allineata a sinistra; le parole in una linea dovranno essere separate da almeno un carattere di spazio; la sillabazione di eventuali parole troppo lunghe non è necessaria.

Requisiti generali del progetto: ogni file .c/.h  dovrà essere ben commentato: per ogni funzione commentare brevemente i parametri di ingresso/uscita e il suo funzionamento generale; nel corpo di ogni funzione commentare le linee di codice più importanti; fornire un makefile per compilare il progetto con un semplice make; fornire un file di testo README con una breve spiegazione dei file inclusi e un breve manuale utente; la versione multi-processo del programma dovrà essere costituita da almeno tre processi concorrenti ed intercomunicanti: uno per leggere il file di ingresso, uno per creare le colonne, ed infine uno per la scrittura del file di output. (Ulteriori suddivisioni del carico di lavoro in più di tre processi sono ammesse.) NON è ammesso l’uso di librerie esterne con funzioni per la manipolazione di stringhe o testo che non siano quelle standard del C. Eccezione: è ammesso l’uso di librerie esterne per l’analisi delle opzioni della linea di comando per il vostro programma.

Suggerimenti: usare nomi di variabili e funzioni corrispondenti al loro significato/utilizzo; usare stdin e stdout per rispettivamente il testo in ingresso e in uscita; sviluppare prima la versiosne mono-processo del programma, poi quella multi-processo; per l’analisi della linea di comando si consiglia getopt, di uso molto semplice e che fa parte della libreria GNU standard del C; concentratevi prima sulla correttezza dei programmi, cioè assicuratevi con più testi di input che i programmi producano un output incolonnato secondo le richieste. Se avete tempo alla fine, ottimizzate il codice per uso di CPU e/o RAM, mantenendone la correttezza; potete usare wc per verificare che il numero delle parole in ingresso e in uscita dei vostri programmi sia lo stesso (usando stdin e stdout nel vostri programmi, questo semplice test si riduce ad una sola linea di comando con l’operatore pipe | della shell).

Il punteggio massimo è 6/30, articolato come segue: correttezza del programma (3/30); architettura del programma e commenti (2/30); usabilità e istruzioni utente (1/30).
```

Output:
```
Sistemi Operativi II     ingresso  è tutto su     solo   allineata   a
Modulo.     Progetto     una  sola  colonna);     sinistra;  le parole
(Homework).              il numero di colonne     in     una     linea
                         per  pagina  su  cui     dovranno      essere
L’obiettivo        è     distribuire       il     separate  da  almeno
implementare      un     testo;  il numero di     un    carattere   di
programma    C   che     linee    per    ogni     spazio;           la
trasformi  un  testo     colonna;   larghezza     sillabazione      di
in  italiano  da una     di    ogni   colonna     eventuali     parole
colonna     a    più     (numero di caratteri     troppo  lunghe non è
colonne    su    più     per   colonna);   la     necessaria.         
pagine  (come ad es.     distanza          in                         
per  una  pagina  di     caratteri   tra  una     Requisiti   generali
quotidiano).    Sono     colonna  di  testo e     del  progetto:  ogni
richieste        due     l’altra.                 file   .c/.h   dovrà
versioni         del                              essere           ben
programma:   una   a     Dati   in  uscita  e     commentato: per ogni
singolo  processo  e     requisiti:  un  file     funzione  commentare
una   multi-processo     di    testo    ASCII     brevemente         i
con    almeno    tre     contenente  il testo     parametri         di
processi                 di input incolonnato     ingresso/uscita e il
concorrenti.             e impaginato secondo     suo    funzionamento
                         i parametri espressi     generale;  nel corpo
Dati  in  ingresso e     dall’utente.      Le     di   ogni   funzione
requisiti:  un  file     pagine sono separate     commentare  le linee
di testo in codifica     dalla   stringa  “\n     di     codice    più
Unicode      (UTF-8)     %%%     \n”;    ogni     importanti;  fornire
contenente  un testo     paragrafo è separato     un    makefile   per
in          italiano     da  una linea vuota;     compilare         il
strutturato       in     la  prima colonna di     progetto    con   un
paragrafi   separati     testo  è a sinistra;     semplice       make;
da  una  o più linee     tutte    le   righe,     fornire  un  file di
vuote       (stringa     tranne  l’ultima, di     testo README con una
contenente  solo  il     ogni       paragrafo     breve    spiegazione
carattere     ‘\n’).     dovranno      essere     dei  file  inclusi e
Ogni   paragrafo   è     allineate         ad     un   breve   manuale
costituito  da una o     entrambi  i  margini     utente;  la versione
più         stringhe     della       colonna;     multi-processo   del
terminate   da  ‘\n’     l’ultima   riga   di     programma      dovrà
(il     testo     in     ogni   paragrafo   è     essere costituita da

 %%% 

almeno  tre processi     sviluppare  prima la     l’operatore  pipe  |
concorrenti       ed     versiosne                della shell).       
intercomunicanti:        mono-processo    del                         
uno  per  leggere il     programma,       poi     Il punteggio massimo
file   di  ingresso,     quella                   è  6/30,  articolato
uno  per  creare  le     multi-processo;  per     come          segue:
colonne,  ed  infine     l’analisi      della     correttezza      del
uno per la scrittura     linea  di comando si     programma    (3/30);
del  file di output.     consiglia getopt, di     architettura     del
(Ulteriori               uso molto semplice e     programma e commenti
suddivisioni     del     che  fa  parte della     (2/30);  usabilità e
carico  di lavoro in     libreria         GNU     istruzioni    utente
più  di tre processi     standard    del   C;     (1/30).             
sono ammesse.) NON è     concentratevi  prima
ammesso   l’uso   di     sulla    correttezza
librerie esterne con     dei  programmi, cioè
funzioni    per   la     assicuratevi con più
manipolazione     di     testi di input che i
stringhe o testo che     programmi  producano
non   siano   quelle     un            output
standard    del   C.     incolonnato  secondo
Eccezione: è ammesso     le   richieste.   Se
l’uso   di  librerie     avete   tempo   alla
esterne          per     fine, ottimizzate il
l’analisi      delle     codice  per  uso  di
opzioni  della linea     CPU     e/o     RAM,
di  comando  per  il     mantenendone      la
vostro programma.        correttezza;  potete
                         usare     wc     per
Suggerimenti:  usare     verificare   che  il
nomi  di variabili e     numero  delle parole
funzioni                 in   ingresso  e  in
corrispondenti    al     uscita   dei  vostri
loro                     programmi   sia   lo
significato/utilizzo     stesso (usando stdin
;   usare   stdin  e     e  stdout nel vostri
stdout           per     programmi,    questo
rispettivamente   il     semplice   test   si
testo  in ingresso e     riduce  ad  una sola
in           uscita;     linea di comando con
```
