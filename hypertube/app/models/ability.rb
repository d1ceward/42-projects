class Ability
  include CanCan::Ability

  def initialize(user)
    can :manage, [Movie, MovieDownload, MovieView]
    can :manage, Comment

    can [:update, :destroy], Comment do |c|
      c.user_id == user.id
    end

    can [:create, :destroy], [UserMovie] do |um|
      um.user_id == user.id
    end
  end
end
