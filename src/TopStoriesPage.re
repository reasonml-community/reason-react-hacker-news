open ReasonJs;

open Utils;

module TopStoriesPage = {
  include ReactRe.Component.Stateful;
  type props = unit;
  type state = {topstories: StoryData.topstories, page: int, loading: bool};
  let name = "TopStoriesPage";
  let getInitialState _ => {topstories: [||], page: 0, loading: false};
  let nearTheBottom unit => distanceFromBottom () < 100;
  let handleLoaded {state} (page, data) => {
    let updatedTopstories = Array.concat [state.topstories, data];
    Some {topstories: updatedTopstories, page: page + 1, loading: false}
  };
  let loadNextPage this =>
    if (this.state.page < 4) {
      StoryData.fetchTopStories this.state.page (this.updater handleLoaded);
      Some {...this.state, loading: true}
    } else {
      None
    };
  let handleScroll this _ =>
    if (nearTheBottom () && not this.state.loading) {
      loadNextPage this
    } else {
      None
    };
  let componentDidMount this => {
    Dom.(Window.addEventListener "scroll" (this.updater handleScroll) window);
    loadNextPage this
  };
  let render {state} => {
    let storyArray =
      if (Array.length state.topstories > 0) {
        Array.mapi
          (fun index story => <StoryListItem key=(string_of_int index) index story />)
          state.topstories
      } else {
        [||]
      };
    <div> (ReactRe.arrayToElement storyArray) </div>
  };
};

include ReactRe.CreateComponent TopStoriesPage;

let createElement = wrapProps ();
