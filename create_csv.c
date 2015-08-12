#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/**
-2 = low
-1 = bass
0 = middle
1 = treble
2 = high
*/
int octave;

// General function to report a failure and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

int main(int argc, char** argv) {
  // make sure we got good command-line arguments.
  if ( argc != 2 )
    fail( "include a .csv file on the command line" );
  remove(argv[1]);
  // Open the point list file.
  FILE *fp = fopen( argv[ 1 ], "ab+" );
  if ( fp == NULL )
    fail( "Can't open input file" );
  remove("temporary.txt");
  FILE *fp2 = fopen( "temporary.txt", "ab+" );
  if ( fp == NULL )
    fail( "Can't open temporary file" );
  remove("temporary2.txt");
  FILE *fp3 = fopen( "temporary2.txt", "ab+" );
  if ( fp == NULL )
    fail( "Can't open temporary2 file" );

  //int tempo = 0;
  //printf("Beats per Minute? : ");
  //scanf("%d", &tempo);
  //tempo = 60000000/tempo;
  //printf("Seed? : ");
  //scanf("%d", seed);
  fprintf(fp, "0, 0, Header, 1, 4, 480\n");
  fprintf(fp, "1, 0, Start_track\n");
  fprintf(fp, "1, 0, Title_t, \"Chaos Encoded\"\n");
  fprintf(fp, "1, 0, Text_t, \"test\"\n");
  fprintf(fp, "1, 0, Copyright_t, \"Joseph Gregory, All Rights Reserved\"\n");
  //fprintf(fp, "1, 0, Tempo, %d\n", tempo);
  fprintf(fp, "1, 0, Tempo, 500000\n");
  fprintf(fp, "1, 0, Time_signature, 4, 2, 8, 8\n");
  fprintf(fp, "1, 0, End_track\n");

  fprintf(fp, "2, 0, Start_track\n");
  fprintf(fp, "2, 0, Title_t, \"Main\"\n");
  fprintf(fp, "2, 0, Program_c, 1, 91\n");

  fprintf(fp2, "3, 0, Start_track\n");
  fprintf(fp2, "3, 0, Title_t, \"Second\"\n");
  fprintf(fp2, "3, 0, Program_c, 3, 94\n");

  fprintf(fp3, "4, 0, Start_track\n");
  fprintf(fp3, "4, 0, Title_t, \"Third\"\n");
  fprintf(fp3, "4, 0, Program_c, 4, 21\n");


  int noteDuration = 300;
  int time = 0;
  int curNote = 60;
  int duration = 270000;
  //int noteChange = 0;
  int noteNum = 0;

  //int noteDuration2 = noteDuration;
  double temp = 0;
  int fugueDelay = duration / 5 - 4000;
  int fugueFinish = fugueDelay * 3;
  int curNote2 = 0;

  int seg = duration/50;
  int noteChanger[50][4] = {{fugueDelay*2-2*seg, 8, 0}, {fugueDelay*2-seg, -4,0}, {fugueDelay*2, -8,0}, {fugueDelay*2 + seg, -4,0}, {fugueDelay*2+seg+seg, 4,0},{fugueDelay*2+noteDuration*8*6+noteDuration*4, 8, -50},{fugueDelay*2+noteDuration*8*6+ noteDuration*32, 8,-50}, {fugueDelay*2+noteDuration*8*6+ noteDuration*64, 10, -50},{fugueDelay*2+noteDuration*8*6+ noteDuration*96, -12, 150}, {seg*29, -7,0}, {seg*36, -7,0}, {seg*38, -8,0}, {seg*40, -12,0}, {seg*45, 4,0}, {seg*49, -12,0}, {duration+5000,0,0}};
  int it = 0;

  int noteHolds[50] = {seg*2, duration};
  int noteHolder[4] = {};//holds sequence
  int p = 0;
  int useSeq[80] = {fugueDelay*2, 0, fugueDelay*2+noteDuration*8, 0, fugueDelay*2+noteDuration*8*2, 4, fugueDelay*2+noteDuration*8*3, 4, fugueDelay*2+noteDuration*8*4, 8, fugueDelay*2+noteDuration*8*5, 8,fugueDelay*2+noteDuration*8*6, 12,fugueDelay*2+noteDuration*8*7, 12,fugueDelay*2+noteDuration*8*8, 16,fugueDelay*2+noteDuration*8*9, 16,fugueDelay*2+noteDuration*8*10, 30,fugueDelay*2+noteDuration*8*10+fugueDelay*4, -20,duration/2+seg*2, -5,duration/2+seg*2+noteDuration*4*1, -7,duration/2+seg*2+noteDuration*4*2, -9,duration/2+seg*2+noteDuration*4*3, -11,duration/2+seg*2+noteDuration*4*4, -7,duration/2+seg*2+noteDuration*4*5, -9,duration/2+seg*2+noteDuration*4*6, -11,duration/2+seg*2+noteDuration*4*1, -13,duration/2+seg*2+noteDuration*4*2, -11,duration/2+seg*2+noteDuration*4*3, -13,duration/2+seg*2+noteDuration*4*4, -15,duration/2+seg*2+noteDuration*4*5, -17,duration/2+seg*2+noteDuration*4*6, -5,duration/2+seg*2+noteDuration*4*1, -7,duration/2+seg*2+noteDuration*4*2, -9,duration/2+seg*2+noteDuration*4*3, -11,duration/2+seg*2+noteDuration*4*4, -5,duration/2+seg*2+noteDuration*4*5, -3,duration/2+seg*2+noteDuration*4*6, -1, duration};
  int j = 0;
  int z = 0;
  int addition = 0;
  int go = 0;

  int Xnote = 0;
  while (time < duration) {
    noteNum++;
    if (time >= noteChanger[it][0]) {//&& noteChanger[it] > 100
      Xnote = noteChanger[it][1];
      curNote += Xnote;
      //fprintf(fp, "Note Duration=== %d, [it+1]: %d, [it]: %d\n", noteChanger[it][2], noteChanger[it][1], noteChanger[it][0]);
      noteDuration += noteChanger[it][2];
      it++;
      //fprintf(fp, "Note Duration=== %d\n", noteChanger[it][2]);
    }
    if (noteNum%4 == 0) {
      //7 = (15-1)/2
      curNote += (rand()%7 - 3) * 2;
      if (time > fugueDelay) {
        temp = ((double)fugueFinish / (double)time);
        curNote2 = curNote - (temp * (double)3);
        if (time > fugueDelay*2 + seg*6) {
          curNote2 -= 4;
        } else if ( time > fugueDelay*2) {
          curNote2 -= 12;
        }
        //fprintf(fp, "TEMP:::: %f\n", temp);
      }
      if (time >= useSeq[j] && noteNum%4 == 0) {
        addition = useSeq[j+1];
        j+=2;
        go = 1;
      }

    } else if (noteNum%2 == 0) {
      curNote += (rand()%3 - 1) * 2;
      curNote2 += (rand()%3 - 1) * 2;
    } else {
      curNote += rand()%3 - 1;
      curNote2 += rand()%3 - 1;
    }
    //if (noteDuration >

    if (time > fugueDelay + 300) {
      fprintf(fp2, "3, %d, Note_on_c, 3, %d, 95\n", time, curNote2);
      fprintf(fp2, "3, %d, Note_off_c, 3, %d, 80\n", time + noteDuration, curNote2);
    }
    if (go ) {//&& (noteNum%4 != 0 || z%4 == 0)
      fprintf(fp3, "4, %d, Note_on_c, 4, %d, 95\n", time, noteHolder[z%4] + addition);
      fprintf(fp3, "4, %d, Note_off_c, 4, %d, 80\n", time + noteDuration, noteHolder[z%4] + addition);
      z++;
      if (z%4 == 3) {
        p = 0;
        go = 0;
      }
    }

    if ((time >= noteHolds[p] && noteNum%4 == 0)|| p%4 != 0) { //record sequence
      noteHolder[p] = curNote;
      if (p < 50) {
        p++;
      }
    }
    if (curNote - noteChanger[it][1] < 43) {
      curNote = 65 - (curNote / 7) - rand()%3;
    }
    if (curNote  + noteChanger[it][1] > 78) {
      curNote = 65 + (curNote / 7) + rand()%3;
    }
    //curNote -= 1;
    fprintf(fp, "2, %d, Note_on_c, 1, %d, 95\n", time, curNote-2);
    time += noteDuration;
    fprintf(fp, "2, %d, Note_off_c, 1, %d, 80\n", time, curNote-2);
    //fprintf(fp, "TIME::: %d, noteDur::: %d\n", time, noteDuration);

  }
  fprintf(fp, "2, %d, End_track\n", duration + noteDuration*2);
  fprintf(fp2, "3, %d, End_track\n", duration + noteDuration*2);
  fprintf(fp3, "4, %d, End_track\n", duration + noteDuration*2);
  fprintf(fp3, "0, 0, End_of_file\n");
  fprintf(fp2, "}");
  char c = 0;
  rewind(fp2);
  while((c=fgetc(fp2))!='}') { //} is used as an EOF
    fputc(c,fp);
  }
  fprintf(fp3, "}");
  rewind(fp3);
  while((c=fgetc(fp3))!='}') { //} is used as an EOF
    fputc(c,fp);
  }
}
