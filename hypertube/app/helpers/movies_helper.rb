module MoviesHelper
  def translate_date(date)
    if params[:locale] == "fr"
      map = {'January' => 'Janvier', 'February' => 'Février', 'March' => 'Mars',
        'April' => 'Avril', 'May' => 'Mai', 'June' => 'Juin',
        'July' => 'Juillet', 'August' => 'Août', 'September' => 'Septembre',
        'October' => 'Octobre', 'November' => 'Novembre', 'December' => 'Décembre'}
      map.each {|k,v| date.sub!(k,v)}
    end
    return date
  end

  def translate_genres(genres)
    if params[:locale] == "fr"
      map = {'Adventure' => 'Aventure', 'Comedy' => 'Comédie', 'Documentary' => 'Documentaire',
        'Family' => 'Famille', 'Fantasy' => 'Fantaisie', 'History' => 'Histoire',
        'Biography' => 'Biographie', 'Horror' => 'Horreur', 'Music' => 'Musique',
        'Mystery' => 'Mystère', 'Sci-Fi' => 'Science-Fiction', 'War' => 'Guerre'}
      map.each {|k,v| genres.sub!(k,v)}
    end
    return genres
  end

  def translate_language(language)
    if params[:locale] == "fr"
      map = {'en' => 'Anglais', 'fr' => 'Français', 'es' => 'Espagnol',
        'it' => 'Italien', 'nl' => 'Néerlandais', 'pl' => 'Pologne',
        'pt' => 'Portugais', 'ro' => 'Roumain', 'sv' => 'Suédois',
        'tr' => 'Turque', 'none' => 'Aucun'}
      map.each {|k,v| language.sub!(k,v)}
    elsif params[:locale] == "en"
      map = {'en' => 'English', 'fr' => 'French', 'es' => 'Spanish',
        'it' => 'Italian', 'nl' => 'Dutch', 'pl' => 'Poland',
        'pt' => 'Portuguese', 'ro' => 'Romanian', 'sv' => 'Swedish',
        'tr' => 'Turkish', 'none' => 'none'}
      map.each {|k,v| language.sub!(k,v)}
    end
    return language
  end
end
