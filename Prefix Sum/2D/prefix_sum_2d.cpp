	int number_of_palindromes[size1][size2];
  
  // Prefix Sum 2D
	for (int i = 0; i < strhash.size(); ++i) {
		for (int j = 1; j < strhash.size(); ++j) {
			number_of_palindromes[i][j] += number_of_palindromes[i][j-1];
		}
	}
	for (int i = 0; i < strhash.size(); ++i) {
		for (int j = strhash.size() - 2; j >= 0; j--) {
			number_of_palindromes[j][i] += number_of_palindromes[j+1][i];
		}
	}
