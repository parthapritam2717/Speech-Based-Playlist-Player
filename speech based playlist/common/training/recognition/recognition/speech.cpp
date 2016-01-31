# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <math.h>
# include <float.h>
# include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
using namespace std;

/*----------------------------------------------------Function declarations starts here---------------------------------------------------- */
FILE *openfile(char *s, char *right);
void split_codebook();
void write_codebook_final();
void print_separator(int n);
void reinitialise();
int read_universe(char *s);
void load_config();
void random_initialise_codebook();
void kmeans();
void populate_bucket();
void calc_min_distance(int number, int index_universe_vector);
void copy_codebook();
long double calculate_distortion();
void update_codebook();
void bucket_sum(int i);
void update_distortion_graph(long double distortion);
void print_bucket(double, int);
long double calculate_distortion_new();
void special_split(int index, int zero);
void update_distortion_change(long double dis);
void update_log();
void read_source_voice(char *s);
void input_address_resolution();
void update_suffix_file_name(int s1, int s2);
void calc_threshold_energy();
void calc_energy_segment();
void copy_speech();
void copy_speech_to_file();
void correct_dc();
void normalise();
void hamming();
void durbin_ai();
void rcalc();
void cepstral_ci();
void update_universe();
void reset_cis();
void generate_universe();
void generate_codebook();
void apply_HMM();
void problem1_solve();
void problem2_solve();
void viterbi();
void initialise_gamma();
void viterbi_initialisation();
void viterbi_recursion();
void viterbi_termination();
void viterbi_state_sequence_backtrack();
void write_qstar_to_file();
void problem3_solve();
void calc_b_bar();
void reEstimate_B_bar();
void calc_a_bar();
void calc_pi_bar();
void calc_geta();
void read_A();
void read_B();
void read_pi();
void read_observation();
void write_a_bar();
void write_b_bar();
void write_xeta();
void copy_ci_vector_separate(char *);
void generate_observation();
void individual_ci(FILE *fp);
void complete_model();
void training();
void testing();


void DisplayErrorBox(LPTSTR lpszFunction);
/*----------------------------------------------------Global variables declaration starts here----------------------------------------------------*/
/*used for solution to problem 1  */
long double Bh[5][32] = { 0 }, Bhavg[5][32] = { 0 }, Bhtemp[5][32] = { 0 };
// N is the number of states and M is the number of distinct observation
long double pi[5];
// probability that at time t=1 it is in state S(i).
long double Ah[5][5] = { 0 }, Ahavg[5][5] = { 0 }, Ahtemp[5][5] = { 0 };
// state trasition probability distribution a(i,j) means probabilty to move to state j  at time (t+1) given it is in state i at time t
long double alpha[35000][5];//TxN
// T is the number of entries in observation sequence. need to calculate T
long double P;
// probability that a given observation sequence was produced by the given model
long double Beta[35000][5];//TxN
int observation[35000] = { 0 };
int T;
int N = 5, Mh = 32;

long double gamma[35000][5] = { 0 };
long double delta[35000][5] = { 0 };
long double scii[35000][5] = { 0 };
long int qstar[35000];
long double pstar;
char ind_vector[200];// to store the address for individual vector


char input_prefix[50];// to store the roll number of the value
int index[2];// store the speech region
long double hamming_weight[320];// to store the hamming weight
char *suffix1;// to store the digit number
int no_of_frame;// to store the number of frames
char *suffix2;//to store the digit instance number
int suf1;//to store the int value of suffix 1
int suf2;// to store the int value of suffix2
char input_voice[200];//to store the address of the file to be read next
long double source_raw[200000];// to store the signal in an array which includes the noise part too
long double frame[320];// to store the frame under consideration for which we will find the ci's
long double source_speech[200000];// store the speech region from the source (only contains speech)
long double energy_frame[200000];// to store the energy of each frame
long double threshold_energy;// to store the threshold energy
int frame_size;// to store the frame size
int shift;// to store the shify value to be used with sliding window
long double  threshold;// the threshold ration for identifying speech region
char input[200];	// to store the address of the universe file
int noOfLine;	// to save the numbre of vectors in the universe codebook
int noOfLine_speech;// noOfLines in the speech region
int codebook_size;	// to store the size of the codebook for which we want to make the code book
char source_universe[200] = { '\0' };	// to store the source universe file address
long double universe[500000][12] = { 0 };	// to store the universe vectors
char delim[] = ",";	// delim is set to , and " " space this variable is used to read data from source with each value separated by delim
long double codebook[100][12] = { 0 };   // to store the codebook 
long double codebook_temp[100][12] = { 0 };   // to store the old codebook 
int weight[] = { 1, 3, 7, 13, 19, 22, 25, 33, 42, 50, 56, 61 };	 // itakura distance calculation weight coefficeients
long double bucket[100][500000] = { 0 };		// to store the vectors in the  buckets 
int bucket_index[100] = { 0 };     // to store upto which index the respective bucket is full with the universe address
long double dist[500000] = { 0 };   // to store the min distance for the code vector
long double distortion_new = 0;   // to store the new distortion value
long double distortion_old = 0;		// to store the old distortion value
long double change_distortion = 0;	// change in distortion
long double sumbucket[12] = { 0 };		// sum of buckets
int M = 1;	// stating codebook size
long double epsilon = 0;				// splitting factor which is fetched from config
long double R[13] = { 0 };// to calculate ris
long double C[13] = { 0 };// to calculate cis
long double E[13] = { 0 }, K[13] = { 0 };
long double A[13][13] = { 0 };// to calculate ais
int p;
long double geta[35000][5][5] = { 0 };
long double pibar[5] = { 0 }, Pi_avg[5] = { 0 }, Pi_final[5] = { 0 };
long double a_bar[5][5] = { 0 }, Ah_avg[5][5] = { 0 }, Ah_final[5][5] = { 0 };
long double b_bar[5][32] = { 0 }, Bh_avg[5][32] = { 0 }, Bh_final[5][32] = { 0 };
long double ind_ci[35000][12] = { 0 };
int temp_obs_len = 0;
int ob[35000] = { 0 };
int Qtemp[35000] = { 0 };
char obs[200];// to store the address for observation vectors
char test[200];
int utter[20] = { 30 };
int words;







/*----------------------------------------------------Function definations starts here------------------------------------*/


/*Driver function for generating the size 32 codebook*/
void generate_codebook(){

	noOfLine = read_universe(source_universe);  // now we have our universe in array and total number of vectors 
	random_initialise_codebook();     // random codebook generated from the universe
	printf("Creating codebook from cepstral universe.........Please wait!!");
	while (M<codebook_size){

		split_codebook();
		print_separator(0);   // for log separation start
		kmeans();
		print_separator(1);  // for log separation end

	}
	write_codebook_final();
	printf("\nCodebook of size %d generated successfully!!\n", codebook_size);

}

/*This function is the driver function for creating the universe */
void generate_universe(){
	printf("Generating cepstral coeff. universe.............. Please Wait!!\n");
	DIR *dp;
	struct dirent *ep;
	char temp[200];

	dp = opendir("E:/common/input/");
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, input_prefix);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			puts(temp);
			/*Now all the processing code*/
			read_source_voice(temp);
			correct_dc();
			copy_speech();
			normalise();
			memset(frame, 0, sizeof(int));
			//copy_speech_to_file();
			// need to do sliding window framing of the speech region and shift of 80 samples then we will operate on that frame
			for (int z = 0; z <= noOfLine_speech - 320; z += shift){
				int x = 0;
				int m = z;
				while (x< m + 320){
					frame[x] = source_speech[m + x];
					//i++;
					x++;
				}
				hamming();
				rcalc();
				durbin_ai();
				cepstral_ci();
				copy_ci_vector_separate(ep->d_name);
				update_universe();
				//printf("h");
			}
			reset_cis();

		}
		(void)closedir(dp);
	}
	else
		perror("Couldn't open the directory");

}





/*To reset all global variables to 0*/

void reset_cis(){
	noOfLine = 0;
	noOfLine_speech = 0;
	for (int i = 0; i < 320; i++){
		frame[i] = 0;
		hamming_weight[i] = 0;
	}
	for (int i = 0; i < 200000; i++){
		source_raw[i] = 0;
		source_speech[i] = 0;

	}
	for (int i = 0; i < 20000; i++){
		energy_frame[i] = 0;
	}
	for (int i = 0; i < 13; i++){
		R[i] = 0;
		C[i] = 0;
		E[i] = 0;
		K[i] = 0;

		for (int j = 0; j < 13; j++){
			A[i][j] = 0;
		}

	}




}

/*To correct the Dc shift if any in the input*/
void correct_dc(){
	int i = 0;
	long double sum = 0, avg = 0;
	for (i = 0; i<noOfLine; i++){
		sum += source_raw[i];
	}
	avg = sum / noOfLine;

	for (i = 0; i<noOfLine; i++){
		source_raw[i] -= (long double)avg;
	}


}

/*To normalise the given speech region */
void normalise(){
	int i = 0; long double maxp = 0, maxneg = 0, max = 0;
	for (i = 0; i<noOfLine_speech; i++){
		if (maxp<source_speech[i])
			maxp = source_speech[i];
		if (maxneg>source_speech[i])
			maxneg = source_speech[i];
	}
	if (abs(maxneg)>abs(maxp)){
		max = abs(maxneg);
	}
	else{
		max = maxp;
	}
	//printf("max=%lf  %lf  %lf\n",maxp, maxneg, max); 
	for (i = 0; i<noOfLine_speech; i++){
		long double normal = ((source_speech[i] / max) * 15000);
		source_speech[i] = normal;
	}

}

/*To calc the hamming window for the given frame*/
void hamming(){
	int x = 0; long double pi = 22 / 7;
	//printf("%d %d\n",i,j);
	for (int i = 0; i<frame_size; i++){
		hamming_weight[x] = 0.54 - 0.46*(cos((2 * pi*x) / (frame_size - 1)));
		frame[x] = frame[x] * hamming_weight[x];
		x++;
	}
}

/*to calculate r values for the frame*/
void rcalc(){
	int k = 1, i = 0; long double sum = 0;
	for (int n = 0; n < 320; n++){
		R[0] = R[0] + (frame[n] * frame[n]);
	}

	for (k; k <= p; k++){
		int j = (frame_size - 1 - k);
		sum = 0;
		for (int m = 0; m <= j; m++){
			sum += frame[m] * frame[m + k];
		}
		R[k] = sum;
	}

}

//to apply durbins algo and find ai's
void durbin_ai(){
	int i = 0;
	long double sum = 0;
	E[0] = R[0];
	A[0][p] = 1;
	K[1] = R[1] / R[0];
	if (R[0] == 0 || (R[0] > 0 && R[0] < .0005)){
		printf("R[0] is very close to zero so can't calculate Ai's\n");
		getch();
		exit(-1);
	}

	//printf("A=%lf\n",A[0][p]);
	for (int i = 1; i <= p; i++){
		sum = 0;
		for (int j = 1; j <= i - 1; j++){

			sum += (A[j][i - 1] * R[i - j]);
		}
		//printf("%lf\n",sum);
		K[i] = (R[i] - sum) / E[i - 1];
		//printf("k=%lf\n",K[i]);
		A[i][i] = K[i];
		for (int j = 1; j <= i - 1; j++){
			A[j][i] = A[j][i - 1] - K[i] * A[i - j][i - 1];
		}
		E[i] = (1 - K[i] * K[i])*E[i - 1];
	}
}

//to calc c'i for the given frame
void cepstral_ci(){
	int m; long double sum = 1;
	for (m = 1; m <= p; m++){
		sum = 0;
		for (int k = 1; k <= m - 1; k++){
			sum = sum + (long double)((k*C[k] * A[m - k][p]) / m);
		}
		C[m] = A[m][p] + sum;
	}
}

// to update the universe and add the latest cepstral coeff
void update_universe(){
	FILE *fps = openfile("E:\\common\\output\\universe.txt", "a");
	//fprintf(fps, "Ci=,");
	for (int i = 1; i <= p; i++){
		//printf("\nC%d=%LLf\n", i, C[i]);
		fprintf(fps, "%.20Lf, ", C[i]);
	}
	fprintf(fps, "\n");
	fclose(fps);
}


/*To calculate the energy of each segment in which there are
320 values or points in each segment*/
void calc_energy_segment(){
	//int *pA=array;
	long double energ = 0;
	int i = 0;// to traverse the source array to make segment
	int j = 0;// to store the index of energy array
	while (i != noOfLine){
		energ = energ + (source_raw[i] * source_raw[i]);
		if ((i + 1) % frame_size == 0){
			energy_frame[j] = energ;
			j++;
			energ = 0;
		}
		i++;
	}
	no_of_frame = j;
}

/*To calc threshold energy for identifying speech region*/
/*To calculate the threshold value of energy  we have taken a small
sample  the number of segments to be considered is fetched from configuration file in the strart the we find the maximum energy in that region*/
void calc_threshold_energy(){
	int i = 0;
	long double thres = -1;
	for (i = 0; i < 5; i++){
		if (thres < energy_frame[i]){
			thres = energy_frame[i];
		}   //printf("threshold value=%d\n",threshold);
	}
	thres += (thres + thres*threshold);
	threshold_energy = thres;

}

/*To identify the speech region and copy the data to speech_region array*/
void copy_speech(){
	int flag = 0;
	for (int i = 0; i < noOfLine; i++){
		/*if (energy_frame[i]>threshold_energy && flag == 0){
		index[0] = i;
		flag = 1;
		}
		else if (energy_frame[i] < threshold_energy && flag == 1){
		index[1] = i;
		flag = 0;
		}*/
		source_speech[i] = source_raw[i];
	}
	// now to copy this speech region to our_speech region array
	/*int j = 0;
	for (int i = index[0] * 320; i <index[1] * 320 + 320; i++){
	source_speech[j] = source_raw[i];
	j++;
	}*/
	noOfLine_speech = noOfLine;
}

/*Write the copy speech_source to a txt file and check*/
void copy_speech_to_file(){
	FILE *fp = openfile("E:\\common\\output\\speech.txt", "a");
	for (int i = 0; i <noOfLine_speech; i++){
		fprintf(fp, "%.20Lf\n", source_speech[i]);
	}
	fclose(fp);
}

/*This function eveluates which digit and the instance of the digit that is to be read*/
void update_suffix_file_name(int s1, int s2){
	char *buf = (char*)malloc(sizeof(char)* 10);
	char *buf1 = (char*)malloc(sizeof(char)* 10);
	suffix1 = (char*)malloc(sizeof(char)* 10);
	suffix2 = (char*)malloc(sizeof(char)* 10);
	suffix1 = itoa(s1, buf, 10);
	suffix2 = itoa(s2, buf1, 10);



}

/*This function helps in address resolution for the audio file*/
void input_address_resolution(){
	strcpy(input_voice, input_prefix);
	strcat(input_voice, "_");
	strcat(input_voice, suffix1);
	strcat(input_voice, "_");
	strcat(input_voice, suffix2);
	strcat(input_voice, ".txt");

}

/*This function reads the sound file and then copy the value to the array*/
void read_source_voice(char *s){
	double number; FILE *fp;
	int count = 0;
	fp = openfile(s, "r");
	char buf[50];
	noOfLine = 0;
	while (fgets(buf, 50, fp) != NULL){
		//printf("%s", buf);

		if (count > 4){

			number = atof(buf);
			source_raw[noOfLine] = number;
			noOfLine += 1;
		}
		count++;
	}
	fclose(fp);

}

/*This function opens a file and returns the file pointer , para meter passed is the file location and mode of file operation*/
FILE *openfile(char *s, char *right){
	FILE *fp = fopen(s, right);
	if (fp == NULL){
		printf("File address invalid exception for the addesss %s", s);
		getch();
		exit(-1);
	}
	return fp;
}

/*This function is to copy the universe vectors from text file to the array*/
int read_universe(char *s){
	int lines = 0;
	int j = 0, i = 0;
	char *token;
	char buf[600] = { '\0' };
	FILE *fp = openfile(s, "r");
	while (fgets(buf, 600, fp)){//&& lines<3
		lines += 1;
		j = 0;
		token = strtok(buf, delim);
		while (token != NULL) {
			double number = atof(token);
			universe[lines - 1][j] = number;
			//printf("%lf\n", source[noOfLine-1][j]);
			j++;
			token = strtok(NULL, delim);
		}
		j++;
	}
	printf("\n%d number of vectors in universe \n", lines);
	fclose(fp);
	return lines;
}

/*This function loads the config file and then initialises all the required parameters for the program*/
void load_config(){
	char bufconf[100];
	char value[20] = { '\0' };
	char temp[40] = { '\0' };
	int len;
	FILE *fp = openfile("E:\\common\\config\\configuration.txt", "r");
	while (fgets(bufconf, 100, fp)){
		int index = -1;
		//strrev(bufconf);
		memset(value, '\0', sizeof(value));
		while ((bufconf[index] != '=')){
			index++;
		}
		len = strlen(bufconf);
		memset(temp, '\0', sizeof(temp));// to set the string to \0
		strncpy(temp, bufconf, index);
		if (strcmp(temp, "codebook_size") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			codebook_size = atoi(value);
		}
		/*if (strcmp(temp, "utter") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			utter = atoi(value);
		}*/
		if (strcmp(temp, "words") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			words = atoi(value);
		}

		if (strcmp(temp, "epsilon") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			epsilon = atof(value);
		}
		if (strcmp(temp, "source") == 0){
			strncpy(source_universe, bufconf + index + 1, len - index - 2);
		}
		if (strcmp(temp, "prefix") == 0){
			strncpy(input_prefix, bufconf + index + 1, len - index - 2);
		}

		// to store the address for individual vector
		if (strcmp(temp, "ind_vector") == 0){
			strncpy(ind_vector, bufconf + index + 1, len - index - 2);
		}
		if (strcmp(temp, "observation") == 0){
			strncpy(obs, bufconf + index + 1, len - index - 2);
		}
		if (strcmp(temp, "testing") == 0){
			strncpy(test, bufconf + index + 1, len - index - 2);
		}
		if (strcmp(temp, "frame_size") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			frame_size = atoi(value);
		}
		if (strcmp(temp, "shift") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			shift = atoi(value);
		}
		if (strcmp(temp, "p") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			p = atoi(value);
		}
		if (strcmp(temp, "threshold") == 0){
			strncpy(value, bufconf + index + 1, len - index - 2);
			//printf("%s",value);
			threshold = atof(value);
		}

	}
	//printf("Codebook size=%d\n", codebook_size);
	fclose(fp);
}

/*Random initialise the codebook for the first time divide the universe into subparts equal to codebook size
and then take the average value for each group of vector  as a code vector for the codebook*/
void random_initialise_codebook(){
	/* initial codebook size is 1*/
	int i = 0;
	for (i = 0; i<noOfLine; i++){
		bucket_sum(i);
	}
	for (i = 0; i<12; i++){
		codebook[0][i] = sumbucket[i] / noOfLine;
		sumbucket[i] = 0;
	}
}

/*this function adds the entire vector from the universe array whose index is stored in our bucket and whose index
is passed to here*/
void bucket_sum(int index){
	int i = 0;
	for (i = 0; i<12; i++){
		sumbucket[i] += universe[index][i];
	}
}

/*This function splits the present codebook and stores the new codebook in a temp codebook from where we
will update the actual codebook later using cop_to original function*/
void split_codebook(){
	int i = 0, j = 0, k = 1;
	// reset temp first
	for (i = 0; i<codebook_size; i++){
		for (j = 0; j<12; j++){
			codebook_temp[i][j] = 0;
		}
	}
	for (i = 0; i<M; i++){
		k = i * 2;
		for (j = 0; j<12; j++){
			codebook_temp[k][j] = codebook[i][j] * (1 + epsilon);
			codebook_temp[k + 1][j] = codebook[i][j] * (1 - epsilon);
		}
	}
	M *= 2;

	// now recopy back the temp to our original codebook
	for (i = 0; i<M; i++){
		for (j = 0; j<12; j++){
			codebook[i][j] = codebook_temp[i][j];

		}
	}

}

/*Populate the buckets with codevector from the universe based on nearest neighbour method*/
void populate_bucket(){
	int k = 0;	// start from the universe vector index 0
	while (k<noOfLine){
		calc_min_distance(M, k);
		k++;
	}
}

/*finding nearest neighbour for each of the bucket and address of each code vectors from the universe into the bucket*/
void calc_min_distance(int number, int index_universe_vector){
	int j = 0, i = 0; long double dmin = 100000000; long double d = 0, s = 0; int min = 0; int num = 0;
	//printf("Am here %d\n",index_universe_vector);
	while (j<number){
		d = 0;
		for (i = 0; i<12; i++){
			d += weight[i] * ((universe[index_universe_vector][i] - codebook[j][i])*(universe[index_universe_vector][i] - codebook[j][i]));
			num++;
		}
		if (dmin>d){
			dmin = d;
			min = j;
		}
		j++;
	}
	dist[index_universe_vector] = dmin;

	bucket[min][bucket_index[min]] = index_universe_vector;
	bucket_index[min] += 1;
	//return dmin;
}

/*update codebook by finding the centroid of all the buckets and then creating the new codebook*/
void update_codebook(){
	int i = 0, j = 0, num = 0, k = 0, max = 0;
	for (i = 0; i<M; i++){
		j = 0; num = 0;
		while (j<bucket_index[i]){

			if (bucket_index[max]<bucket_index[i]){
				max = i;
			}
			bucket_sum(bucket[i][j]); num++;
			bucket[i][j] = 0;	 // to reset the bucket after codebook updation
			j++;
		}

		// to print the bucket contents into the log file
		for (k = 0; k<12; k++){
			if (num != 0){
				sumbucket[k] = sumbucket[k] / num;
				codebook[i][k] = sumbucket[k];
				sumbucket[k] = 0;		//to reinitilise the sumbucket index to 0 for next populate bucket call
			}
		}
		bucket_index[i] = 0; // to reinitilise the bucket index to 0 for next populate bucket call
	}

}

/*This function counts the total distortion caused by the new codebook */
long double calculate_distortion(){
	int i = 0; long double d = 0;
	for (i = 0; i<noOfLine; i++){
		d += dist[i];

	}
	return (d / noOfLine);
}
void print_bucket_contents(){
	FILE *fp;
	int i = 0, j = 0;
	fp = openfile("E:\\common\\output\\log.txt", "a");
	fprintf(fp, "The bucket contents are: \n  ");
	for (i = 0; i<M; i++){
		fprintf(fp, "%d  ", bucket_index[i]);
	}
	fprintf(fp, "\n");

	fclose(fp);
}

/*This function implements the kmeans algo and gives an optimal codebook */
void kmeans(){
	int i = 0, iteration = 1;
	populate_bucket();	 // bucket populated using the nearest neighbour method		
	print_bucket_contents();
	update_codebook();	// update the codebook after bucket population
	distortion_new = calculate_distortion();
	print_bucket(distortion_new, iteration);
	update_distortion_graph(distortion_new);
	for (i = 0; i<noOfLine; i++){
		dist[i] = 0; // to reset the dist array for reuse in future
	}
	do{
		iteration++;
		populate_bucket();	// bucket populated using the nearest neighbour method		
		print_bucket_contents();
		update_codebook();	// update the codebook after bucket population
		distortion_old = distortion_new;
		distortion_new = calculate_distortion();//calculate_distortion();	// new distortion calculated after updating the codebook
		print_bucket(distortion_new, iteration);
		for (i = 0; i<noOfLine; i++){
			dist[i] = 0; // to reset the dist array for reuse in future
		}
		change_distortion = abs(distortion_old - distortion_new);
		update_distortion_graph(distortion_new);// need to put this change in distortion to a csv file for making the graph to verify our operation
	} while (change_distortion>0.001);

}

/*To print the bucket contents after each bucket updata*/
void print_bucket(double dis, int iteration){
	FILE *fp;
	int i = 0, j = 0;
	fp = openfile("E:\\common\\output\\log.txt", "a");

	fprintf(fp, "\nCodebook after %d iteration of codebook size %d:\n", iteration, M);
	for (i = 0; i<M; i++){
		for (j = 0; j<12; j++){
			fprintf(fp, "%.20Lf,", codebook[i][j]);
		}
		fprintf(fp, "\n");
	}
	//fprintf(fp,"\n");
	fprintf(fp, "The distortion after %d iteration is:\n %lf\n\n", iteration, dis);
	fprintf(fp, "---------------------------------------------------------------------------------------------------------------------\n");

	fclose(fp);
}

/*To update the distortion csv */
void update_distortion_graph(long double a){
	FILE *fp;
	fp = openfile("E:\\common\\output\\distortion.csv", "a");
	fprintf(fp, "%.20Lf\n", a);
	fclose(fp);

}

/*To handle the empty cell problem*(not called from anywhere)*/
void special_split(int index, int zero){
	int i = 0;
	long double temp;
	for (i = 0; i<12; i++){
		temp = codebook[index][i];
		codebook[zero][i] = codebook[index][i] * (1 - epsilon);
		codebook[index][i] = codebook[index][i] * (1 + epsilon);

	}
}

void purge_log_files(){
	FILE *fp = openfile("E:\\common\\output\\distortion.csv", "w");
	fclose(fp);
	fp = openfile("E:\\common\\output\\log.txt", "w");
	fclose(fp);
	fp = openfile("E:\\common\\output\\universe.txt", "w");
	fclose(fp);
	fp = openfile("E:\\common\\output\\speech.txt", "w");
	fclose(fp);
	fp = openfile("E:\\common\\output\\codebook.txt", "w");
	fclose(fp);
	DIR *dp;
	struct dirent *ep;
	char temp[200];
	char ind[200];
	strcpy(ind, ind_vector);
	dp = opendir(ind);
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, ind_vector);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			//puts(temp);
			remove(input_voice);
		}

	}






}
void print_separator(int n){
	FILE *fp;
	int i = 0, j = 0;
	fp = openfile("E:\\common\\output\\log.txt", "a");
	if (n == 0){
		fprintf(fp, "========================================Start of k-means for codebook size %d===================================\n\n", M);
	}
	else{
		fprintf(fp, "========================================End of k-means for codebook size %d======================================\n\n", M);
	}
	fclose(fp);
}

void write_codebook_final(){
	FILE *fp;
	int i = 0, j = 0;
	fp = openfile("E:\\common\\output\\codebook.txt", "w");
	for (i = 0; i<M; i++){
		for (j = 0; j<12; j++){
			fprintf(fp, "%.20Lf,", codebook[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

}

void write_a_bar(){
	//write alpha_bar to file
	FILE *fp = openfile("E:\\common\\output\\a_bar.txt", "w");
	int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			fprintf(fp, "%.20E ", a_bar[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	// write beta_bar to file	
	fp = openfile("E:\\common\\output\\b_bar.txt", "w");
	//int i, j;
	for (i = 0; i < N; i++){
		for (j = 0; j < Mh; j++){
			fprintf(fp, "%.20E ", b_bar[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

	// write xeta to file
	fp = openfile("E:\\common\\output\\xeta.txt", "w");
	//int i, j;
	for (i = 0; i < T; i++){
		for (j = 0; j < 5; j++){
			for (int k = 0; k < 5; k++){
				fprintf(fp, "%.20E  ", geta[i][j][k]);;
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
		fprintf(fp, "\n");
		fprintf(fp, "\n");
	}

	fclose(fp);


	// write pibar to file
	fp = openfile("E:\\common\\output\\pi_bar.txt", "w");
	//int i, j;


	for (int k = 0; k < 5; k++){
		fprintf(fp, "%.20E  ", pibar[k]);;
	}
	fprintf(fp, "\n");
	fclose(fp);


	// write gamma to file	
	fp = openfile("E:\\common\\output\\gamma.txt", "w");
	//int i, j;
	for (i = 0; i < T; i++){
		for (j = 0; j < N; j++){
			fprintf(fp, "%5.6E ", gamma[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);




}

/* Functions for problem 1 calculation*/
void write_alpha_beta_to_file(){
	//write alpha to file
	FILE *fp = openfile("E:\\common\\output\\alpha.txt", "w");
	int i, j;
	for (i = 0; i < T; i++){
		for (j = 0; j < N; j++){
			fprintf(fp, "%5.6E ", alpha[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	// write beta to file
	fp = openfile("E:\\common\\output\\beta.txt", "w");
	for (i = 0; i < T; i++){
		for (j = 0; j < N; j++){
			fprintf(fp, "%5.6E ", Beta[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

void read_A(){
	int j = 0, i = 0;
	//char buf[600] = { '\0' };
	int lines = 0;
	//char *token;
	FILE *fp = openfile("E:\\common\\demo_hmm\\a.txt", "r");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			fscanf(fp, "%Lf", &Ah[i][j]);

		}
	}
	//printf("%1.40Lf", Ah[0][0]);
	fclose(fp);
}
void read_B(){
	int j = 0, i = 0;
	//char buf[600] = { '\0' };
	int lines = 0;
	long double k = (double)1 / 32;
	//char *token;
	FILE *fp = openfile("E:\\common\\demo_hmm\\b.txt", "r");
	for (i = 0; i < N; i++){
		for (j = 0; j < Mh; j++){
			//fscanf(fp, "%.20Lf", &Bh[i][j]);			
			Bh[i][j] = k;
			//printf("%lf", Bh[0][0]);
		}
	}
	fclose(fp);
}
void read_pi(){

	int j = 0, i = 0;
	//char buf[600] = { '\0' };
	int lines = 0;
	//char *token;
	FILE *fp = openfile("E:\\common\\demo_hmm\\pi.txt", "r");
	for (i = 0; i < N; i++){
		fscanf(fp, "%lf", &pi[i]);
	}
	fclose(fp);
}
void problem1_calc(){
	long double sum; int i, j, t;
	// Forward method calculate alpha
	/* Initialisation step for problem 1*/

	for (i = 0; i <= 5 - 1; i++){
		alpha[0][i] = pi[i] * Bh[i][observation[0]];
	}

	/*Induction step*/

	for (t = 0; t <= T - 2; t++){
		for (j = 0; j <= 5 - 1; j++){
			sum = 0;
			for (i = 0; i <= 5 - 1; i++){
				sum += alpha[t][i] * Ah[i][j];
			}
			alpha[t + 1][j] = sum*Bh[j][observation[t + 1]];
		}
	}

	/*Termination stage*/
	sum = 0;
	for (i = 0; i <= 5 - 1; i++){
		sum += alpha[T - 1][i];
	}
	P = sum;
	// Backward method calculate Beta	

	//printf("Probablity=%E\n", P);
	/*Initialisation*/
	for (i = 0; i <= 5 - 1; i++){
		Beta[T - 1][i] = 1;
	}

	/*Induction*/
	//sum = 0;
	for (t = T - 2; t >= 0; t--){

		for (i = 0; i <= 5 - 1; i++){
			long double sum = 0;
			for (j = 0; j <= 5 - 1; j++){
				sum += Ah[i][j] * Bh[j][observation[t + 1]] * Beta[t + 1][j];
			}
			Beta[t][i] = sum;
		}

	}
	//printf("Hello");
}
void problem1_solve(){
	//read_observation();	
	//read_A();
	//read_B();
	//read_pi();
	problem1_calc();
	write_alpha_beta_to_file();



}

/*Functions for problem 2 calculation */
void initialise_gamma(){
	int i, t, j;
	for (t = 0; t < T; t++){
		for (i = 0; i < N; i++){
			double sum = 0;
			for (j = 0; j < N; j++){
				sum += alpha[t][j] * Beta[t][j];
			}
			gamma[t][i] = (long double)(alpha[t][i] * Beta[t][i]) / sum;

		}
	}

	//printf("he");
}
void viterbi_initialisation(){
	int i, j, t;
	for (i = 0; i < N; i++){
		delta[0][i] = pi[i] * Bh[i][observation[i]];
		scii[0][i] = 0;
	}
}
void viterbi_recursion(){
	int t, j, i;
	for (t = 1; t < T; t++){
		for (j = 0; j < N; j++){
			long double max = 0, temp;
			int index = -1;

			for (i = 0; i < N; i++){
				temp = delta[t - 1][i] * Ah[i][j];
				if (temp>max){
					max = temp;
					index = i;
				}
			}
			scii[t][j] = index;
			delta[t][j] = max*Bh[j][observation[t]];
		}
	}



	//printf("h");
}
void viterbi_termination(){
	int i = 0;
	double max = 0;
	int index = -1;
	for (i = 0; i < N; i++){
		if (delta[T - 1][i]>max){
			max = delta[T - 1][i];
			index = i;
		}
	}
	pstar = max;
	qstar[T - 1] = index;
	//printf("The P* value = %E\n", pstar);




}
void viterbi_state_sequence_backtrack(){
	int t;
	for (t = T - 2; t >= 0; t--){
		qstar[t] = scii[t + 1][qstar[t + 1]];
	}
	//printf("The qstar value is : ");
	//for (int z = 0; z < T; z++)
	//printf("%d ", qstar[z]);
}
void write_qstar_to_file(){
	// qstar write to file
	FILE *fp = openfile("E:\\common\\output\\qstar.csv", "w");
	int i, j;
	for (i = 0; i < T; i++){
		fprintf(fp, "%ld, %ld\n", qstar[i], observation[i]);
	}
	fclose(fp);

}
void viterbi(){
	viterbi_initialisation();
	viterbi_recursion();
	viterbi_termination();
	viterbi_state_sequence_backtrack();
	write_qstar_to_file();
	//printf("sd");
}
void problem2_solve(){
	initialise_gamma();
	viterbi();
}
/*problem 2 solving functions ends here*/


/*Function for problem 3 calculation */

void calc_geta(){
	int t, i, j;
	long double temp;
	for (t = 0; t < T - 1; t++)
	{
		temp = 0;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				temp += alpha[t][i] * Ah[i][j] * Bh[j][observation[t + 1]] * Beta[t + 1][j];
			}
		}

		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				geta[t][i][j] = alpha[t][i] * Ah[i][j] * Bh[j][observation[t + 1]] * Beta[t + 1][j];
				geta[t][i][j] /= temp;
			}

		}
	}
	//printf("h");

}
void calc_pi_bar(){
	for (int i = 0; i < 5; i++){
		pibar[i] = gamma[0][i];
	}

	//printf("h");
}
void calc_a_bar(){
	int t, i, j, k;
	double t1, t2;
	for (i = 0; i<N; i++)
	{
		t2 = 0;
		for (t = 0; t<T - 1; t++)
		{
			t2 += gamma[t][i];
		}

		for (j = 0; j<N; j++)
		{
			//fill A[i][j]
			t1 = 0;
			for (t = 0; t<T - 1; t++)
			{
				t1 += geta[t][i][j];

			}
			a_bar[i][j] = t1 / t2;
		}
	}
	//printf("h");


}
void reEstimate_B_bar(){
	int j, k;
	int count;
	long double max = 0;
	int maxindex = 0;
	for (j = 0; j<N; j++) //For each row
	{
		max = 0;
		maxindex = 0;
		for (k = 0; k<Mh; k++)
		{
			if (max < b_bar[j][k])
			{
				max = b_bar[j][k];
				maxindex = k;
			}
		}
		count = 0;
		for (k = 0; k<Mh; k++)
		{
			if (b_bar[j][k] < pow((long double)10, -100))
			{
				b_bar[j][k] = pow((long double)10, -20);
				count++;
			}
		}
		b_bar[j][maxindex] -= (pow((long double)10, -20) *count);
	}
	/*int j, k;
	int count;
	long double max = 0;
	long double sum = 0;
	int maxindex = 0;
	for (j = 0; j<N; j++) //For each row
	{
	sum = 0;
	max = 0;
	maxindex = 0;
	for (k = 0; k<Mh; k++)
	{
	if (max < b_bar[j][k])
	{
	max = b_bar[j][k];
	maxindex = k;
	}
	}
	count = 0;
	for (k = 0; k<Mh; k++)
	{
	if (b_bar[j][k] < 1.0e-15)
	{
	sum += ((1.0e-15) - b_bar[j][k]);
	b_bar[j][k] = 1.0e-15;//pow((long double)10, -15);
	count++;
	}
	}
	b_bar[j][maxindex] -= sum;//(1.0e-15)*count;//(pow((long double)10, -20) *count);
	printf("he");
	}*/
	//printf("hh\n");
}

void calc_b_bar(){
	//reestimate B : frequency logic
	// calculate B_bar

	int l, j, k, t;

	for (l = 0; l<T; l++)
		Qtemp[l] = -1;

	for (j = 0; j < N; j++)
	{
		int count = 0;
		for (t = 0; t < T; t++)
		{
			if (j == qstar[t])
			{
				count++;
				Qtemp[t] = j;
			}
		}

		for (k = 0; k < Mh; k++)
		{
			int count1 = 0;
			for (l = 0; l < T; l++)
			{
				if (observation[l] == k && Qtemp[l] == j)
				{
					count1++;
				}
			}
			if (count != 0)
			{
				b_bar[j][k] = (long double)count1 / count;
			}
			else
			{
				b_bar[j][k] = 0;
			}
		}

		for (l = 0; l < T; l++)
			Qtemp[l] = -1;

	}

	reEstimate_B_bar();

}
void problem3_solve(){
	calc_geta();
	calc_pi_bar();
	calc_a_bar();
	calc_b_bar();
	//printf("h");
}



/*Fucntions for problem 3 calculation ends her*/

/*This function is to write the individual cepstral coefficients for the individual utterences*/
void copy_ci_vector_separate(char *temp){


	char address[200];
	strcpy(address, ind_vector);
	//"E:\\project\\output\\individual_vector\\";			
	strcat(address, temp);

	FILE *fps = openfile(address, "a");
	//fprintf(fps, "Ci=,");
	for (int i = 1; i <= p; i++){
		//printf("\nC%d=%LLf\n", i, C[i]);
		fprintf(fps, "%.20Lf, ", C[i]);
	}
	fprintf(fps, "\n");
	fclose(fps);

}
/*void demo(){

FILE *fp = openfile("..\\output\\demo.txt", "w");
int i, j; long double s[2] = { 0 };

for (j = 0; j < 2; j++){
fprintf(fp, "%.20Lf\n",23.0000000236612345678);
}

fclose(fp);
fp = openfile("..\\output\\demo.txt", "r");
for (i = 0; i < 2; i++){
fscanf(fp, "%Lf", &s[i]);
//printf("%LF", s);
}

//printf("%E", s);
fclose(fp);

}*/

void calc_observation(int k){
	//min dist logic
	int len = temp_obs_len;
	int j = 0, i = 0; long double dmin = 100000000; long double d = 0, s = 0; int min = 0; int num = 0;
	//printf("Am here %d\n",index_universe_vector);	

	for (int j = 0; j < 32; j++){
		d = 0;
		for (i = 0; i<12; i++){
			d += weight[i] * ((ind_ci[k][i] - codebook[j][i])*(ind_ci[k][i] - codebook[j][i]));
			num++;
		}
		if (dmin>d){
			dmin = d;
			min = j;
		}

	}
	ob[k] = min + 1;
}

void individual_ci(FILE *fp){
	//fprintf(fps, "Ci=,");
	temp_obs_len = 0;
	int lines = 0;
	int j = 0, i = 0;
	char *token;
	char buf[600] = { '\0' };
	//FILE *fp = openfile(s, "r");
	while (fgets(buf, 600, fp)){//&& lines<3
		lines += 1;
		j = 0;
		token = strtok(buf, delim);
		while (token != NULL) {
			double number = atof(token);
			ind_ci[lines - 1][j] = number;
			//printf("%lf\n", source[noOfLine-1][j]);
			j++;
			token = strtok(NULL, delim);
		}
		j++;
	}
	//printf("\n%d number of vectors in tex \n", lines);
	temp_obs_len = lines;
	fclose(fp);

}

void reset_observation(){
	for (int i = 0; i < 35000; i++){
		observation[i] = 0;
		ob[i] = 0;
		for (int j = 0; j < 12; j++){
			ind_ci[i][j] = 0;
		}
	}
	temp_obs_len = 0;
}

void print_ob(char *temp){
	char address[200];//"E:\\project\\output\\observation\\";
	strcpy(address, obs);
	strcat(address, temp);
	FILE *f = openfile(address, "w");
	//fprintf(fps, "Ci=,");
	for (int i = 0; i <temp_obs_len; i++){
		//printf("\nC%d=%LLf\n", i, C[i]);
		//printf("%d\n", ob[i]);
		fprintf(f, "%d\n", ob[i]);
	}
	fclose(f);
	//printf("he");
}

void generate_observation(){
	printf("Generating observation sequence!!\n");
	// reset all global variables			
	DIR *dp;
	struct dirent *ep;
	char temp[200], ind[200];
	strcpy(ind, ind_vector);
	dp = opendir(ind);
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, ind);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			FILE *fps = openfile(input_voice, "r");
			individual_ci(fps);
			fclose(fps);
			for (int k = 0; k < temp_obs_len; k++){
				calc_observation(k);
			}
			print_ob(ep->d_name);
			reset_observation();

		}
	}

}




void reset_model(){
	for (int e = 0; e < N; e++){
		for (int f = 0; f < N; f++){
			a_bar[e][f] = 0;;
		}
		//fprintf(fp, "\n");
	}
	for (int e = 0; e < N; e++){
		for (int f = 0; f < N; f++){
			b_bar[e][f] = 0;;
		}
		//fprintf(fp, "\n");
	}

	for (int e = 0; e < N; e++){
		pi[e] = pibar[e];
	}



}

/*training of the model is done by this function*/

void training(){
	printf("Training the system!!\n");
	char add[150] = "E:\\common\\training_log.txt";
	FILE *fp = openfile(add, "w");
	fclose(fp);

	int y;
	bool flag = false;
	for (int i = 0; i <= words - 1; i++){
		fp = openfile(add,"a");
		fprintf(fp, "Training for word %d\n", i);
		fclose(fp);
		//printf("Training for word %d\n", i);
		for (y = 0; y <= 2; y++){
			memset(Ah_avg, 0, sizeof(Ah_avg));
			memset(Bh_avg, 0, sizeof(Bh_avg));
			memset(Pi_avg, 0, sizeof(Pi_avg));
			for (int j = 1; j <= utter[i]; j++){
				/*Code to read the required observation vector*/
				// reset all values
				reset_observation();
				reset_model();
				long double psold = 0, psnew = 0;
				int qsnew[35000] = { 0 };
				int k = 0;
				char buf[10] = { '\0' };
				int lines = 0;
				char *token;
				update_suffix_file_name(i, j);
				char address[200] = "E:\\common\\output\\observation\\";
				//char address[200] = "..\\input\\demo_hmm\\1";
				memset(input_voice, '\0', sizeof(char));
				strcpy(input_voice, address);
				strcat(input_voice, suffix1);
				strcat(input_voice, "_");
				strcat(input_voice, suffix2);
				strcat(input_voice, ".txt");
				FILE *fp = openfile(input_voice, "r");
				while (fgets(buf, 10, fp)){//&& lines<3		
					double number = atof(buf);
					observation[k] = number - 1;
					k++;
				}
				lines = k;
				T = lines;
				//printf("%d", T);
				//printf("\n%d number of lines in the observation \n", lines);
				fclose(fp);

				/*Observation vector reading complete*/
				/* Read the default A,B,PI*/
				if (y <= 0){
					read_A();
					read_B();
					read_pi();

				}
				else if (y >= 1){
					for (int e = 0; e < N; e++){
						for (int f = 0; f < N; f++){
							Ah[e][f] = Ah_final[e][f];
						}
						//fprintf(fp, "\n");
					}
					for (int e = 0; e < N; e++){
						for (int f = 0; f < Mh; f++){
							Bh[e][f] = Bh_final[e][f];
						}
						//fprintf(fp, "\n");
					}
					for (int e = 0; e < N; e++){
						pi[e] = Pi_final[e];
					}
				}

				int x = 0;
				problem1_solve();
				problem2_solve();
				problem3_solve();
				for (int e = 0; e < N; e++){
					for (int f = 0; f < N; f++){
						Ah[e][f] = a_bar[e][f];
					}
					//fprintf(fp, "\n");
				}
				for (int e = 0; e < N; e++){
					for (int f = 0; f < Mh; f++){
						Bh[e][f] = b_bar[e][f];
					}
					//fprintf(fp, "\n");
				}

				for (int e = 0; e < N; e++){
					pi[e] = pibar[e];
				}
				psnew = pstar;
				psold = psnew;
				do{
					//psold = psnew;
					problem1_solve();
					problem2_solve();
					problem3_solve();
					for (int e = 0; e < N; e++){
						for (int f = 0; f < N; f++){
							Ah[e][f] = a_bar[e][f];
						}
						//fprintf(fp, "\n");
					}
					for (int e = 0; e < N; e++){
						for (int f = 0; f < Mh; f++){
							Bh[e][f] = b_bar[e][f];
						}
						//fprintf(fp, "\n");
					}

					for (int e = 0; e < N; e++){
						pi[e] = pibar[e];
					}
					//psold = psnew;
					psnew = pstar;
					x++;
				} while ((psnew - psold) != 0 && x < 10);
				fp = openfile(add, "a");
				fprintf(fp, "pstar= %E\n", psold);
				fclose(fp);
				printf("pstar=%E\n", psold);
				//printf("Qstar=");
				/*for (int c = 0; c < T; c++){
				printf("%d ", qstar[c]);
				}*/
				//now add to average value and then write to file
				for (int e = 0; e < N; e++){
					for (int f = 0; f < N; f++){
						Ah_avg[e][f] += Ah[e][f];
					}
					//fprintf(fp, "\n");
				}
				for (int e = 0; e < N; e++){
					for (int f = 0; f < Mh; f++){
						Bh_avg[e][f] += Bh[e][f];
					}
					//fprintf(fp, "\n");
				}
				for (int e = 0; e < N; e++){
					Pi_avg[e] += pi[e];
				}
			}
			/*now divide by 20 to find the average Ah,Bh,Pi*/
			for (int e = 0; e < N; e++){
				for (int f = 0; f < N; f++){
					Ah_avg[e][f] /= utter[i];
				}
				//fprintf(fp, "\n");
			}
			for (int e = 0; e < N; e++){
				for (int f = 0; f < Mh; f++){
					Bh_avg[e][f] /= utter[i];
				}
				//fprintf(fp, "\n");
			}
			for (int e = 0; e < N; e++){
				Pi_avg[e] /= utter[i];
			}
			/*now copy the average values to the final array and then use this as the initial input*/
			for (int e = 0; e < N; e++){
				for (int f = 0; f < N; f++){
					Ah_final[e][f] = Ah_avg[e][f];
				}
				//fprintf(fp, "\n");
			}
			for (int e = 0; e < N; e++){
				for (int f = 0; f < Mh; f++){
					Bh_final[e][f] = Bh_avg[e][f];
				}
				//fprintf(fp, "\n");
			}
			for (int e = 0; e < N; e++){
				Pi_final[e] = Pi_avg[e];
			}

			//printf("");


		}
		//printf("");
		/*write the values to individual files*/
		update_suffix_file_name(i, 2);
		char add[200] = "E:\\common\\output\\A\\A";
		//char address[200] = "..\\input\\demo_hmm\\1";
		strcpy(input_voice, add);
		strcat(input_voice, suffix1);
		//strcat(input_voice, "_");		
		strcat(input_voice, ".txt");
		FILE *fp = openfile(input_voice, "w");
		long double sum = 0;
		printf("Printing the A row sum for word %d:\n", i);
		for (int i = 0; i < N; i++){
			sum = 0;
			for (int j = 0; j < N; j++){
				fprintf(fp, "%.20E ", Ah_final[i][j]); sum += Ah_final[i][j];
			}
			fprintf(fp, "\n"); printf("%lf\n", sum);
		}
		fclose(fp);
		char adds[200] = "E:\\common\\output\\B\\B";
		//char address[200] = "..\\input\\demo_hmm\\1";
		strcpy(input_voice, adds);
		strcat(input_voice, suffix1);
		//strcat(input_voice, "_");		
		strcat(input_voice, ".txt");
		fp = openfile(input_voice, "w");
		printf("Printing the B row sum for word %d:\n", i);
		for (int i = 0; i < N; i++){
			sum = 0;
			for (int j = 0; j < Mh; j++){
				fprintf(fp, "%.20E ", Bh_final[i][j]); sum += Bh_final[i][j];
			}
			fprintf(fp, "\n"); printf("%lf\n", sum);
		}
		fclose(fp);
		// now for pi
		char addss[200] = "E:\\common\\output\\PI\\p";
		//char address[200] = "..\\input\\demo_hmm\\1";
		strcpy(input_voice, addss);
		strcat(input_voice, suffix1);
		//strcat(input_voice, "_");		
		strcat(input_voice, ".txt");
		fp = openfile(input_voice, "w");
		int sum1 = 0;
		printf("Printing the P row sum for word %d:\n", i);
		sum = 0;
		for (int e = 0; e < N; e++){
			fprintf(fp, "%.20E ", Pi_final[e]); sum1 += Pi_final[e];
		}
		printf("%d\n", sum1);
		fclose(fp);
		//printf("");
	}
}
/*Testing the utterances*/
void testing(){
	DIR *dp;
	struct dirent *ep;
	char temp[200];
	strcpy(temp, test);
	dp = opendir(temp);
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, test);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			//puts(temp);			
			printf("For digit %s\n", ep->d_name);
			memset(Ah_avg, 0, sizeof(Ah_avg));
			memset(Bh_avg, 0, sizeof(Bh_avg));
			memset(Pi_avg, 0, sizeof(Pi_avg));
			memset(Ah, 0, sizeof(Ah));
			memset(Bh, 0, sizeof(Bh));
			memset(pi, 0, sizeof(pi));
			reset_observation();
			T = 0;
			reset_model();
			int k = 0;
			char buf[10] = { '\0' };
			int lines = 0;
			char *token;
			FILE *fp = openfile(input_voice, "r");
			while (fgets(buf, 10, fp)){//&& lines<3		
				double number = atof(buf);
				observation[k] = number - 1;
				k++;
			}
			lines = k;
			T = lines;
			//printf("%d", T);
			//printf("\n%d number of lines in the observation \n", lines);
			fclose(fp);
			/*Now read the lamda and compare with the value store the max probability and digit number */
			long double Pmax = -DBL_MAX;
			int max_number = -1;
			for (int z = 0; z <= 9; z++){
				char add[200] = "E:\\common\\output\\A\\A";
				update_suffix_file_name(z, 0);
				strcpy(input_voice, add);
				strcat(input_voice, suffix1);
				strcat(input_voice, ".txt");
				fp = openfile(input_voice, "r");
				for (int i = 0; i < N; i++){
					for (int j = 0; j < N; j++){
						fscanf(fp, "%lf", &Ah[i][j]);
					}
				}
				fclose(fp);
				char adds[200] = "E:\\common\\output\\B\\B";
				update_suffix_file_name(z, 0);
				strcpy(input_voice, adds);
				strcat(input_voice, suffix1);
				strcat(input_voice, ".txt");
				fp = openfile(input_voice, "r");
				for (int i = 0; i < N; i++){
					for (int j = 0; j < Mh; j++){
						fscanf(fp, "%lf", &Bh[i][j]);
					}
				}
				fclose(fp);
				char addss[200] = "E:\\common\\output\\PI\\P";
				update_suffix_file_name(z, 0);
				strcpy(input_voice, addss);
				strcat(input_voice, suffix1);
				strcat(input_voice, ".txt");
				fp = openfile(input_voice, "r");
				for (int i = 0; i < N; i++){
					fscanf(fp, "%lf", &pi[i]);
				}
				fclose(fp);
				/*now model read apply problem 1 and select the max probability*/
				problem1_calc();
				if (P>Pmax){
					Pmax = P;
					max_number = z;
				}
				printf("");
			}
			printf("%d  \n", max_number);
			//printf("The probability is:%E\n", Pmax);
			printf("\n");
		}
	}
}




/*This function will implememt a working speech reconnisation application using the Hmm modules */
void complete_model(){
	training();

}


void purge_previous_model(){
	char temp[200];
	char ind[200];
	strcpy(ind, "E:\\common\\output\\A\\");
	DIR *dp;
	struct dirent *ep;
	FILE *fp;
	dp = opendir(ind);
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, ind);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			remove(input_voice);
		}
	}
	memset(ind, '\0', sizeof(char));
	strcpy(ind, "E:\\common\\output\\B\\");
	dp = opendir(ind);
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, ind);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			remove(input_voice);
		}
	}
	memset(ind, '\0', sizeof(char));
	strcpy(ind, "E:\\common\\output\\PI\\");
	dp = opendir(ind);
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			if (ep->d_name[0] == '.' || ep->d_name[0] == '.'){
				continue;
			}
			memset(temp, '\0', sizeof(char));
			memset(input_voice, '\0', sizeof(char));
			strcpy(temp, ind);
			strcat(temp, ep->d_name);
			strcpy(input_voice, temp);
			remove(input_voice);
		}
	}
}

void load_count(){
	char address[200] = "E:\\common\\config\\counter.txt";
	char line[20];
	int i = 0;
	FILE *fp = openfile(address,"r");
	while (1) {
		if (fgets(line,20, fp) == NULL) break;
		utter[i] = atoi(line);
		//printf("%3d: %s", i, line);
		i++;
	}
	fclose(fp);
}



int main(){
	load_count();// read the count of language files then initialise the utter array
	load_config();// to load the configuration file and read the necesary parameters
	purge_log_files();   // to delete any previous files
	purge_previous_model();// to delete previous model 
	generate_universe();// generate universe for the given input files
	generate_codebook();// generate an optimal codebook fro the given universe	
	generate_observation();
	complete_model();
	//getch();
	return 0;
}

