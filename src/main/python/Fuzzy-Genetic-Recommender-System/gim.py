from itertools import count
import numpy as np
from settings import NO_OF_GENRES, NO_OF_FEATURES

# Genre columns
genre_cols = ['unknown', 'Action', 'Adventure', 'Animation', 'Children\'s', 'Comedy', 'Crime', 'Documentary', 'Drama',
          'Fantasy','Film-Noir', 'Horror', 'Musical', 'Mystery', 'Romance', 'Sci-Fi', 'Thriller', 'War', 'Western']

# Initialize numpy arrays
gr = np.zeros(NO_OF_GENRES)
gf = np.zeros(NO_OF_GENRES)
rgr = np.zeros(NO_OF_GENRES)
rgf = np.zeros(NO_OF_GENRES)
mrgf = np.zeros(NO_OF_GENRES)

# tr - total_ratings
# gr - genre_rating
# gf - genre_frequency
# rgr - realtive_genre_ratings
# rgf - relative_genre_frequency
# mrgf - modified_relative_genre_frequency
# gim - genre interestingness measure


def total_rating(i):
    """Get total of given or particular rating."""
    total = 0
    for k in count['rating']:
        total = total + k
    return total


def genre_rating(movies):
    """Get genre rating for movies"""
    for i in range(0, NO_OF_GENRES):
        gr[i] = np.dot(movies['rating'], movies[genre_cols[i]])
    return gr


def genre_frequency(movies):
    """Get genre frequency for all the movies i.e. how many movies have a particular genre."""
    for i in range(0, NO_OF_GENRES):
        gf[i] = movies[genre_cols[i]].sum()
    return gf


def relative_genre_rating(gr, tr):
    """Relative Genre Rating= Genre Ratings/ Total Rating"""
    for i in range(0, NO_OF_GENRES):
        rgr[i] = gr[i] / tr
    return rgr


def relative_genre_frequency(gf, tf):
    """Relative Genre Frequency=Genre Frequency/Total Frequency"""
    for i in range(0, NO_OF_GENRES):
        rgf[i] = gf[i] / tf
    return rgf


def add_for_mrgf(movies):
    total = np.zeros(NO_OF_GENRES)
    for i in range(0, NO_OF_GENRES):
        m_t = movies.loc[movies[genre_cols[i]] == 1]
        for j in m_t['rating']:
            total[i] = total[i] + (j - 2)
    return total


def modified_relative_genre_frequency(movies, tf):
    """Modified Relative Genre Frequency = add_for_mrgf/(3*Total Frequency)"""
    added = add_for_mrgf(movies)
    for i in range(0, NO_OF_GENRES):
        mrgf[i] = (added[i]) / (3.0 * tf)
    return mrgf


def gim_final(user_movies, i):
    """Get GIM of movies of particular user"""

    gim_list = [0] * NO_OF_FEATURES
    tf = user_movies.shape[0]
    # print tf
    tr = 0
    for k in user_movies['rating']:
        tr = tr + k
    movies = user_movies.loc[user_movies['rating'] >= 3.0]

    gr = genre_rating(movies)
    # gf = genre_frequency(movies)
    rgr = relative_genre_rating(gr, tr)
    # rgf = relative_genre_frequency(gf, tf)
    mrgf = modified_relative_genre_frequency(movies, tf)

    nf = 5.0
    for i in range(0, NO_OF_GENRES):
        gim_list[i] = (2 * nf * mrgf[i] * rgr[i]) / (rgr[i] + mrgf[i])
    gim_list = np.nan_to_num(gim_list)
    return gim_list
